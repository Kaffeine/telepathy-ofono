/**
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Tiago Salem Herrmann <tiago.herrmann@canonical.com>
 */

#ifndef OFONOCALLCHANNEL_H
#define OFONOCALLCHANNEL_H

#include <QObject>

#include <TelepathyQt/Constants>
#include <TelepathyQt/BaseChannel>
#include <TelepathyQt/BaseCall>
#include <TelepathyQt/Types>

// qofono
#include <qofonovoicecall.h>

#include "connection.h"

class oFonoConnection;

class oFonoCallChannel : public QOfonoVoiceCall
{
    Q_OBJECT
public:
    oFonoCallChannel(oFonoConnection *conn, QString phoneNumber, uint targetHandle, QString voiceObj, QObject *parent = 0);
    ~oFonoCallChannel();
    Tp::BaseChannelPtr baseChannel();

    void onHangup(uint reason, const QString &detailedReason, const QString &message, Tp::DBusError* error);
    void onAccept(Tp::DBusError*);
    void onMuteStateChanged(const Tp::LocalMuteState &state, Tp::DBusError *error);
    void onHoldStateChanged(const Tp::LocalHoldState &state, const Tp::LocalHoldStateReason &reason, Tp::DBusError *error);
    void onDTMFStartTone(uchar event, Tp::DBusError *error);
    void onDTMFStopTone(Tp::DBusError *error);
    void onSplit(Tp::DBusError *error);
    Tp::CallState callState();

Q_SIGNALS:
    void splitted();
    void merged();
    void closed();
    void multipartyCallHeld();
    void multipartyCallActive();

private Q_SLOTS:
    void onOfonoCallStateChanged(const QString &state);
    void onDtmfComplete(bool success);
    void onSwapCallsComplete(bool success);
    void sendNextDtmf();
    void init();
    void onAnswerComplete(bool success);
    void onHangupComplete(bool success);

    void onOfonoMuteChanged(bool mute);
    void onMultipartyChanged(bool multiparty);
    void onDisconnectReason(const QString &reason);

private:
    QString mObjPath;
    QString mPreviousState;
    bool mIncoming;
    bool mRequestedHangup;
    Tp::BaseChannelPtr mBaseChannel;
    QString mPhoneNumber;
    oFonoConnection *mConnection;
    uint mTargetHandle;
    Tp::BaseChannelHoldInterfacePtr mHoldIface;
    Tp::BaseChannelSplittableInterfacePtr mSplittableIface;
    Tp::BaseCallMuteInterfacePtr mMuteIface;
    Tp::BaseChannelCallTypePtr mCallChannel;
    Tp::BaseCallContentDTMFInterfacePtr mDTMFIface;
    Tp::BaseCallContentPtr mCallContent;
    bool mDtmfLock;
    QStringList mDtmfPendingStrings;
    bool mMultiparty;
};

#endif // OFONOCALLCHANNEL_H
