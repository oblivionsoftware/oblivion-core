/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_BASE_H_
#define _OBLIVION_CORE_BASE_H_

#ifdef WIN32
    #pragma warning(disable: 4251)
    #pragma warning(disable: 4275)

    #define OBLIVION_WINDOWS
    #define OBLIVION_PLATFORM_NAME "Windows"

    #ifdef OBLIVION_CORE_EXPORTS
        #define OB_CORE_API __declspec(dllexport)
    #else
        #define OB_CORE_API __declspec(dllimport)
    #endif
#else
    #define OB_CORE_API
#endif

#endif /* _OBLIVION_CORE_BASE_H_ */
