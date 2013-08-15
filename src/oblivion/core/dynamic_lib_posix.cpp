/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/dynamic_lib.h>

#include <dlfcn.h>

#include <oblivion/core/exception.h>

namespace oblivion {

/**
 * The private implementation of DynamicLib for posix.
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

    void* handle_;

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

DynamicLib::Impl::Impl(const std::string& path) {
    handle_ = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);

    if (!handle_) {
        OB_THROW("Unable to load library: %s", path.c_str());
    }
}

/*****************************************************************************/

DynamicLib::Impl::~Impl() {
    dlclose(handle_);
}

/*****************************************************************************/

void* DynamicLib::Impl::getFunction(const std::string& name) {
    void* result = dlsym(handle_, name.c_str());

    if (!result) {
        OB_THROW("Unable to find function with name: %s", name.c_str());
    }

    return result;
}

/*****************************************************************************/

}
