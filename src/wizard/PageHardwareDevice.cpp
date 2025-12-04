// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: The Monero Project

#include "PageHardwareDevice.h"
#include "ui_PageHardwareDevice.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>

#include "WalletWizard.h"

PageHardwareDevice::PageHardwareDevice(WizardFields *fields, QWidget *parent)
        : QWizardPage(parent)
        , ui(new Ui::PageHardwareDevice)
        , m_fields(fields)
{
    ui->setupUi(this);

    ui->combo_deviceType->addItem("Ledger", DeviceType::LEDGER);
    ui->combo_deviceType->addItem("Trezor", DeviceType::TREZOR);

    connect(ui->btnOptions, &QPushButton::clicked, this, &PageHardwareDevice::onOptionsClicked);

    // Update device type immediately when user selects it
    // This ensures PageWalletFile can use the correct default wallet name
    connect(ui->combo_deviceType, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){
        m_fields->deviceType = static_cast<DeviceType>(ui->combo_deviceType->itemData(index).toInt());
    });
}

void PageHardwareDevice::initializePage() {
    ui->radioNewWallet->setChecked(true);
}

int PageHardwareDevice::nextId() const {
    // Check if user requested subaddress lookahead configuration
    if (m_fields->showSetSubaddressLookaheadPage) {
        return WalletWizard::Page_SetSubaddressLookahead;
    }

    // Check if user is restoring and needs to set restore height
    if (m_fields->showSetRestoreHeightPage) {
        return WalletWizard::Page_SetRestoreHeight;
    }

    // Go directly to wallet file page (which will then go to password page)
    return WalletWizard::Page_WalletFile;
}

bool PageHardwareDevice::validatePage() {
    m_fields->deviceType = static_cast<DeviceType>(ui->combo_deviceType->currentData().toInt());
    m_fields->showSetRestoreHeightPage = ui->radioRestoreWallet->isChecked();
    return true;
}

bool PageHardwareDevice::isComplete() const {
    return true;
}

void PageHardwareDevice::onOptionsClicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Options");

    QVBoxLayout layout;
    QCheckBox check_subaddressLookahead("Set subaddress lookahead");
    check_subaddressLookahead.setChecked(m_fields->showSetSubaddressLookaheadPage);

    layout.addWidget(&check_subaddressLookahead);
    QDialogButtonBox buttons(QDialogButtonBox::Ok);
    layout.addWidget(&buttons);
    dialog.setLayout(&layout);
    connect(&buttons, &QDialogButtonBox::accepted, [&dialog]{
        dialog.close();
    });
    dialog.exec();

    m_fields->showSetSubaddressLookaheadPage = check_subaddressLookahead.isChecked();
}