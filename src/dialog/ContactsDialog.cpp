// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: The Monero Project

#include "ui_ContactsDialog.h"
#include "ContactsDialog.h"

#include "constants.h"
#include "libwalletqt/WalletManager.h"
#include "utils/Utils.h"

ContactsDialog::ContactsDialog(QWidget *parent, const QString &address, const QString &name)
        : WindowModalDialog(parent)
        , ui(new Ui::ContactsDialog)
{
    ui->setupUi(this);
    setMinimumWidth(400);

    ui->lineEdit_address->setText(address);
    ui->lineEdit_name->setText(name);
    if (!name.isEmpty()) {
        ui->lineEdit_name->setFocus();
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this](){
        QString addr = ui->lineEdit_address->text().trimmed();
        if (!addr.isEmpty() && !WalletManager::addressValid(addr, constants::networkType)) {
            Utils::showError(this, "Invalid Address", "Please enter a valid Monero address.");
            return;
        }
        m_address = addr;
        m_name = ui->lineEdit_name->text();
        accept();
    });

    this->adjustSize();
}

QString ContactsDialog::getAddress() {
    return m_address;
}

QString ContactsDialog::getName() {
    return m_name;
}

ContactsDialog::~ContactsDialog() = default;