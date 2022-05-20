#include "vstcomponenthandler.h"

using namespace mu::vst;
using namespace mu::async;

DEF_CLASS_IID(VstComponentHandler);

Channel<PluginParamId, PluginParamValue> VstComponentHandler::pluginParamChanged() const
{
    return m_paramChanged;
}

Notification VstComponentHandler::pluginParamsChanged() const
{
    return m_paramsChangedNotify;
}

Steinberg::tresult VstComponentHandler::beginEdit(Steinberg::Vst::ParamID /*id*/)
{
    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::performEdit(Steinberg::Vst::ParamID id, Steinberg::Vst::ParamValue valueNormalized)
{
    m_paramChanged.send(std::move(id), std::move(valueNormalized));

    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::endEdit(Steinberg::Vst::ParamID /*id*/)
{
    m_paramsChangedNotify.notify();

    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::restartComponent(Steinberg::int32 /*flags*/)
{
    m_paramsChangedNotify.notify();

    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::setDirty(Steinberg::TBool /*state*/)
{
    m_paramsChangedNotify.notify();

    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::requestOpenEditor(Steinberg::FIDString /*name*/)
{
    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::startGroupEdit()
{
    return Steinberg::kResultOk;
}

Steinberg::tresult VstComponentHandler::finishGroupEdit()
{
    m_paramsChangedNotify.notify();

    return Steinberg::kResultOk;
}
