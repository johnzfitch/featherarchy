// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: The Monero Project

#include "WalletUnlockWidget.h"
#include "ui_WalletUnlockWidget.h"

#include <QKeyEvent>
#include <QPushButton>

#include "utils/Utils.h"
#include "libwalletqt/Wallet.h"

WalletUnlockWidget::WalletUnlockWidget(QWidget *parent, Wallet *wallet)
        : QWidget(parent)
        , ui(new Ui::WalletUnlockWidget)
        , m_wallet(wallet)
{
    ui->setupUi(this);
    this->reset();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setAutoDefault(true);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &WalletUnlockWidget::tryUnlock);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &WalletUnlockWidget::closeWallet);

    ui->frame_sync->hide();
    if (m_wallet) {
        connect(m_wallet, &Wallet::syncStatus, [this](quint64 height, quint64 target, bool daemonSync){
            ui->frame_sync->show();
            ui->label_sync->setText(Utils::formatSyncStatus(height, target, daemonSync));
        });
    }
}

void WalletUnlockWidget::secureWipePassword() {
    if (ui && ui->line_password) {
        QString text = ui->line_password->text();
        text.fill('0');
        ui->line_password->clear();
    }
}

void WalletUnlockWidget::setWalletName(const QString &walletName) {
    ui->label_fileName->setText(walletName);
}

void WalletUnlockWidget::reset() {
    ui->label_incorrectPassword->hide();
    this->secureWipePassword();
    ui->line_password->setFocus();
}

void WalletUnlockWidget::incorrectPassword() {
    ui->label_incorrectPassword->show();
    this->secureWipePassword();
}

void WalletUnlockWidget::tryUnlock() {
    QString password = ui->line_password->text();
    this->secureWipePassword();
    emit unlockWallet(password);
}

void WalletUnlockWidget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            emit ui->buttonBox->accepted();
            e->accept();
            break;
        case Qt::Key_Escape:
            emit ui->buttonBox->rejected();
            e->accept();
            break;
        default:
            QWidget::keyPressEvent(e);
    }
}

WalletUnlockWidget::~WalletUnlockWidget() {
    this->secureWipePassword();
}