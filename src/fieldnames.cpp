#include "fieldnames.h"

FieldNames::FieldNames(QObject *parent) :
    QObject(parent)
{
}

QString FieldNames::getName(Fields cn, QDltSettingsManager *settings)
{
    switch(cn)
    {
    case Index:
        return QString("Index");
    case Time:
        return QString("Time");
    case TimeStamp:
        return QString("Timestamp");
    case Counter:
        return QString("Count");
    case tag:
        return QString("Tag");
    case ProcId:
        if(settings == NULL)
        {
            return QString("Pid");
        }
        switch(settings->showPidDesc){
        case 0:
             return QString("Pid");
        case 1:
             return QString("Pid Desc");
        }
    case ThreadId:
        if(settings == NULL)
        {
            return QString("Tid");
        }
        switch(settings->showTidDesc){
        case 0:
             return QString("Tid");
        case 1:
             return QString("Tid Desc");
        }
    case SessionId:
        if(settings == NULL)
        {
            return QString("SessionId");
        }
        switch(settings->showSessionName){
        case 0:
             return QString("SessionId");
        case 1:
             return QString("SessionName");
        }
    case Type:
        return QString("Type");
    case LogLevel:
        return QString("LogLevel");
    case Mode:
        return QString("Mode");
    case ArgCount:
        return QString("#Args");
    case Payload:
        return QString("Payload");
    case MessageId:
        return QString("MsgID");
    default:
        if (cn>=Arg0)
        {
            return QString("Arg%1").arg(cn-Arg0);
        }
        else
        return QString();
    }
}

int FieldNames::getColumnWidth(Fields cn, QDltSettingsManager *settings)
{
    Q_UNUSED(settings)
    int width;
    switch(cn)
    {
    case FieldNames::Index       : width=  50;break;
    case FieldNames::Time        : width= 150;break;
    case FieldNames::TimeStamp   : width=  70;break;
    case FieldNames::Counter     : width=  40;break;
    case FieldNames::tag       : width=  40;break;
    case FieldNames::ProcId       : width=  40;break;
    case FieldNames::ThreadId   : width=  40;break;
    case FieldNames::SessionId   : width=  70;break;
    case FieldNames::Type        : width=  50;break;
    case FieldNames::LogLevel     : width=  50;break;
    case FieldNames::Mode        : width=  50;break;
    case FieldNames::ArgCount    : width=  40;break;
    case FieldNames::Payload     : width=1200;break;
    case FieldNames::MessageId   : width=  90;break;
    default                      : width=  50;break;
    }
    return width;
}

QVariant FieldNames::getColumnAlignment(Fields cn, QDltSettingsManager *settings)
{
    switch(cn)
    {
        case FieldNames::Index:         return QVariant(Qt::AlignRight  | Qt::AlignVCenter);
        case FieldNames::Time:          return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::TimeStamp:     return QVariant(Qt::AlignRight  | Qt::AlignVCenter);
        case FieldNames::Counter:       return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::tag:         return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::ProcId:
            switch(settings->showPidDesc)
            {
            case 0:  return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
            case 1:  return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
            default: return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
            }
        case FieldNames::ThreadId:
            switch(settings->showTidDesc)
            {
            case 0:  return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
            case 1:  return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
            default: return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
            }
        case FieldNames::Type:           return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::LogLevel:        return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::Mode:           return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        case FieldNames::ArgCount:       return QVariant(Qt::AlignRight  | Qt::AlignVCenter);
        case FieldNames::Payload:        return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
        case FieldNames::MessageId:      return QVariant(Qt::AlignRight  | Qt::AlignVCenter);
        case FieldNames::SessionId:      return QVariant(Qt::AlignRight  | Qt::AlignVCenter);
        default:                         return QVariant(Qt::AlignLeft   | Qt::AlignVCenter);
    }

}
bool FieldNames::getColumnShown(Fields cn,QDltSettingsManager *settings)
{
    switch (cn)
    {
        case(FieldNames::Index       ):return  settings->showIndex     ;
        case(FieldNames::Time        ):return  settings->showTime      ;
        case(FieldNames::TimeStamp   ):return  settings->showTimestamp ;
        case(FieldNames::Counter     ):return  settings->showCount     ;
        case(FieldNames::tag       ):return  settings->showtag     ;
        case(FieldNames::ProcId       ):return  settings->showPid      ;
        case(FieldNames::ThreadId   ):return  settings->showTid      ;
        case(FieldNames::SessionId   ):return  settings->showSessionId ;
        case(FieldNames::Type        ):return  settings->showType      ;
        case(FieldNames::LogLevel     ):return  settings->showLogLevel   ;
        case(FieldNames::Mode        ):return  settings->showMode      ;
        case(FieldNames::ArgCount    ):return  settings->showNoar      ;
        case(FieldNames::Payload     ):return  settings->showPayload   ;
        case(FieldNames::MessageId   ):return  settings->showMsgId     ;
        default: return true;
	}
return true;
}
