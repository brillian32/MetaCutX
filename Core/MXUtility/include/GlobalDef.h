//
// Created by 17305 on 2023/11/28.
//

#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#ifdef _WIN32
#ifdef EXPORT_DLL
#define MX_API __declspec(dllexport)
#else
#define MX_API __declspec(dllimport)
#endif
#endif


#endif //GLOBALDEF_H
