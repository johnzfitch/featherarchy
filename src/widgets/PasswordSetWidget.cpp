// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: The Monero Project

#include "PasswordSetWidget.h"
#include "ui_PasswordSetWidget.h"

PasswordSetWidget::PasswordSetWidget(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::PasswordSetWidget)
{
    ui->setupUi(this);

    connect(ui->line_password, &QLineEdit::textChanged, this, &PasswordSetWidget::onPasswordEntryChanged);
    connect(ui->line_confirmPassword, &QLineEdit::textChanged, this, &PasswordSetWidget::onPasswordEntryChanged);

    ui->label_match->setHidden(true);
}

QString PasswordSetWidget::password() {
    if (!this->passwordsMatch()) {
        return {};
    }

    return ui->line_password->text();
}

bool PasswordSetWidget::passwordsMatch() {
    return ui->line_password->text() == ui->line_confirmPassword->text();
}

void PasswordSetWidget::resetFields() {
    this->secureWipe();
    ui->line_password->setText("");
    ui->line_confirmPassword->setText("");
}

void PasswordSetWidget::secureWipe() {
    // Securely wipe password fields by overwriting memory before clearing
    if (ui->line_password) {
        QString text = ui->line_password->text();
        text.fill('0');
        ui->line_password->clear();
    }
    if (ui->line_confirmPassword) {
        QString text = ui->line_confirmPassword->text();
        text.fill('0');
        ui->line_confirmPassword->clear();
    }
}

void PasswordSetWidget::onPasswordEntryChanged() {
    ui->label_match->setHidden(this->passwordsMatch());
    emit passwordEntryChanged();
}

PasswordSetWidget::~PasswordSetWidget() = default;