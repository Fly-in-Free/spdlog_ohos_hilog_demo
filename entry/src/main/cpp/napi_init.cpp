#include "napi/native_api.h"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/ohos_hilog_sink.h"

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;

}

static napi_value TestSpdLogNapi(napi_env env, napi_callback_info info) 
{
    auto hilog_sink = std::make_shared<spdlog::sinks::ohos_hilog_sink_mt>("spdlog_napi", 0x00FF);
    hilog_sink->set_level(spdlog::level::level_enum::trace);
    
    spdlog::logger logger("spdlog_napi", {hilog_sink});
    logger.set_level(spdlog::level::level_enum::trace);
    
    logger.trace("this is a trace message");
    logger.debug("this is a debug message");
    logger.info("this is a info message");
    logger.warn("this is a warn message");
    logger.error("this is a error message");
    logger.critical("this is a critical message");
    return nullptr; // void
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "testSpdLogNapi", nullptr, TestSpdLogNapi, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
