/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/dynamic_lib.h>

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
    explicit Impl(const std::string& path);

    /** 
     * @see DynamicLib::~DynamicLib.
     */
    ~Impl();

    /**
     * @see DynamicLib::getFunction.
     */
    void* getFunction(const std::string& name);

    std::string path_;

    HMODULE handle_;

};

/*****************************************************************************/

DynamicLib::DynamicLib(const std::string& path) 
    : impl_(new Impl(path)) {
}

/*****************************************************************************/

DynamicLib::~DynamicLib() {
}

/*****************************************************************************/

void* DynamicLib::getFunction(const std::string& name) {
    return impl_->getFunction(name);
}

/*****************************************************************************/

const std::string& DynamicLib::path() const {
    return impl_->path_;
}

/*****************************************************************************/

DynamicLib::Impl::Impl(const std::string& path)
    : path_(path) {

    handle_ = LoadLibrary(path.c_str());

    if (!handle_) {
        OB_THROW("Unable to load library: %s", path.c_str());
    }
}

/*****************************************************************************/

DynamicLib::Impl::~Impl() {
    FreeLibrary(handle_);
}

/*****************************************************************************/

void* DynamicLib::Impl::getFunction(const std::string& name) {
    void* result = GetProcAddress(handle_, name.c_str());

    if (!result) {
        OB_THROW("Unable to find function with name: %s", name.c_str());
    }

    return result;
}

/*****************************************************************************/

}
