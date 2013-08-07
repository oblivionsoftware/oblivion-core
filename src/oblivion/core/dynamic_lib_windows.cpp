/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/dynamic_lib.h>

#include <string>

#include <oblivion/core/exception.h>
#include <oblivion/core/windows.h>

namespace oblivion {

/**
 * The private implementation of DynamicLib for windows.
 */
struct DynamicLib::Impl {

    /**
     * @see DynamicLib::DynamicLib.
     */
    explicit Impl(const char* path);

    /** 
     * @see DynamicLib::~DynamicLib.
     */
    ~Impl();

    /**
     * @see DynamicLib::getFunction.
     */
    void* getFunction(const char* name);

    HMODULE handle_;
};

/*****************************************************************************/

DynamicLib::DynamicLib(const char* path) 
    : impl_(new Impl(path)) {
}

/*****************************************************************************/

DynamicLib::~DynamicLib() {
}

/*****************************************************************************/

void* DynamicLib::getFunction(const char* name) {
    return impl_->getFunction(name);
}

/*****************************************************************************/

DynamicLib::Impl::Impl(const char* path) {
    handle_ = LoadLibrary(path);

    if (!handle_) {
        OB_THROW(std::string("Unable to load library: ") + path);
    }
}

/*****************************************************************************/

DynamicLib::Impl::~Impl() {
    FreeLibrary(handle_);
}

/*****************************************************************************/

void* DynamicLib::Impl::getFunction(const char* name) {
    void* result = GetProcAddress(handle_, name);

    if (!result) {
        OB_THROW(std::string("Unable to find function with name: ") + name);
    }

    return result;
}

/*****************************************************************************/

}
