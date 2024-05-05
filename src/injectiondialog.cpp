/**
 * @licence app begin@
 * Copyright (C) 2011-2012  BMW AG
 *
 * This file is part of COVESA Project Dlt Viewer.
 *
 * Contributions are licensed to the COVESA Alliance under one or more
 * Contribution License Agreements.
 *
 * \copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a  copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \file injectiondialog.cpp
 * For further information see http://www.covesa.global/.
 * @licence end@
 */

#include "injectiondialog.h"
#include "ui_injectiondialog.h"

#include "qdltsettingsmanager.h"

InjectionDialog::InjectionDialog(QString procid,QString conid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InjectionDialog)
{
    ui->setupUi(this);
    ui->processidComboBox->setEditText(procid);
    ui->threadidComboBox->setEditText(conid);
}

InjectionDialog::~InjectionDialog()
{
    delete ui;
}

void InjectionDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void InjectionDialog::setProcessId(QString text) { ui->processidComboBox->setEditText(text); }
void InjectionDialog::setThreadId(QString text) { ui->threadidComboBox->setEditText(text); }
void InjectionDialog::setServiceId(QString text) { ui->serviceidComboBox->setEditText(text); }
void InjectionDialog::setData(QString text) { ui->dataComboBox->setEditText(text); }
void InjectionDialog::setDataBinary(bool mode) { ui->binaryRadioButton->setChecked(mode);ui->textRadioButton->setChecked(!mode); }

QString InjectionDialog::getProcessId() { return ui->processidComboBox->currentText(); }
QString InjectionDialog::getThreadId() { return ui->threadidComboBox->currentText(); }
QString InjectionDialog::getServiceId() { return ui->serviceidComboBox->currentText(); }
QString InjectionDialog::getData() { return ui->dataComboBox->currentText(); }
bool InjectionDialog::getDataBinary() { return ui->binaryRadioButton->isChecked(); }

void InjectionDialog::updateHistory()
{
    QStringList list;
    list = QDltSettingsManager::getInstance()->value("injection/processid").toStringList();
    ui->processidComboBox->clear();
    foreach(QString text,list)
       ui->processidComboBox->addItem(text);

    list = QDltSettingsManager::getInstance()->value("injection/threadid").toStringList();
    ui->threadidComboBox->clear();
    foreach(QString text,list)
       ui->threadidComboBox->addItem(text);

    list = QDltSettingsManager::getInstance()->value("injection/serviceid").toStringList();
    ui->serviceidComboBox->clear();
    foreach(QString text,list)
       ui->serviceidComboBox->addItem(text);

    list = QDltSettingsManager::getInstance()->value("injection/data").toStringList();
    ui->dataComboBox->clear();
    foreach(QString text,list)
       ui->dataComboBox->addItem(text);

}

void InjectionDialog::storeHistory()
{
    QStringList list;

    list = QDltSettingsManager::getInstance()->value("injection/processid").toStringList();
    list.removeAll(getProcessId());
    list.prepend(getProcessId());
    while (list.size() > INJECTION_MAX_HISTORY)
        list.removeLast();
    QDltSettingsManager::getInstance()->setValue("injection/processid",list);

    list = QDltSettingsManager::getInstance()->value("injection/threadid").toStringList();
    list.removeAll(getThreadId());
    list.prepend(getThreadId());
    while (list.size() > INJECTION_MAX_HISTORY)
        list.removeLast();
    QDltSettingsManager::getInstance()->setValue("injection/threadid",list);

    list = QDltSettingsManager::getInstance()->value("injection/serviceid").toStringList();
    list.removeAll(getServiceId());
    list.prepend(getServiceId());
    while (list.size() > INJECTION_MAX_HISTORY)
        list.removeLast();
    QDltSettingsManager::getInstance()->setValue("injection/serviceid",list);

    list = QDltSettingsManager::getInstance()->value("injection/data").toStringList();
    list.removeAll(getData());
    list.prepend(getData());
    while (list.size() > INJECTION_MAX_HISTORY)
        list.removeLast();
    QDltSettingsManager::getInstance()->setValue("injection/data",list);

}

