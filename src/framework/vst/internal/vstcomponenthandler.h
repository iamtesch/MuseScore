#ifndef MU_VST_VSTCOMPONENTHANDLER_H
#define MU_VST_VSTCOMPONENTHANDLER_H

#include "async/notification.h"
#include "async/channel.h"

#include "vsttypes.h"

namespace mu::vst {
class VstComponentHandler : public Steinberg::FObject, public IComponentHandler, private IAdvancedComponentHandler
{
public:
    static Steinberg::FUnknown* createInstance()
    {
        return static_cast<IComponentHandler*>(new VstComponentHandler());
    }

    VstComponentHandler() = default;
    virtual ~VstComponentHandler() = default;

    async::Channel<PluginParamId, PluginParamValue> pluginParamChanged() const;
    async::Notification pluginParamsChanged() const;

    OBJ_METHODS(VstComponentHandler, Steinberg::FObject)
    REFCOUNT_METHODS(Steinberg::FObject)
    DEFINE_INTERFACES
    DEF_INTERFACE(IComponentHandler)
    DEF_INTERFACE(IAdvancedComponentHandler)
    END_DEFINE_INTERFACES(Steinberg::FObject)

    static const Steinberg::FUID iid;

private:
    Steinberg::tresult beginEdit(Steinberg::Vst::ParamID id) override;
    Steinberg::tresult performEdit(Steinberg::Vst::ParamID id, Steinberg::Vst::ParamValue valueNormalized) override;
    Steinberg::tresult endEdit(Steinberg::Vst::ParamID id) override;
    Steinberg::tresult restartComponent(Steinberg::int32 flags) override;

    Steinberg::tresult setDirty(Steinberg::TBool state) override;
    Steinberg::tresult requestOpenEditor(Steinberg::FIDString name) override;
    Steinberg::tresult startGroupEdit() override;
    Steinberg::tresult finishGroupEdit() override;

    async::Channel<PluginParamId, PluginParamValue> m_paramChanged;
    async::Notification m_paramsChangedNotify;
};
}

DECLARE_CLASS_IID(VstComponentHandler, 0xD45406B9, 0x3A2D4443, 0x9DAD9BA9, 0x85A1454B)

#endif // MU_VST_VSTCOMPONENTHANDLER_H
