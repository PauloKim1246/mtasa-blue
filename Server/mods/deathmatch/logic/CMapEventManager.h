/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CMapEventManager.h
 *  PURPOSE:     Map event manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "lua/CLuaArguments.h"
#include "CMapEvent.h"
#include <list>

class CMapEventManager
{
public:
    CMapEventManager();
    ~CMapEventManager();

    bool                          Add(CLuaMain* pLuaMain, const char* szName, const CLuaFunctionRef& iLuaFunction, bool bPropagated, EEventPriorityType eventPriority, float fPriorityMod);
    bool                          Delete(CLuaMain* pLuaMain, const char* szName = NULL, const CLuaFunctionRef& iLuaFunction = CLuaFunctionRef());
    void                          DeleteAll();
    bool                          HandleExists(CLuaMain* pLuaMain, const char* szName, const CLuaFunctionRef& iLuaFunction);
    bool                          HasEvents() const { return m_bHasEvents; }
    void                          GetHandles(CLuaMain* pLuaMain, const char* szName, lua_State* luaVM);
    const std::vector<CMapEvent*> GetHandlesByServerRPCFunction(eServerRPCFunctions eServerRPCFunction) const;

    bool Call(const char* szName, const CLuaArguments& Arguments, class CElement* pSource, class CElement* pThis, class CPlayer* pCaller = NULL);

private:
    void TakeOutTheTrash();
    void AddInternal(CMapEvent* pMapEvent);
    void DeleteInternal(CMapEvent* pMapEvent);
    void DisableServerRPCFunction(eServerRPCFunctions eServerRPCFunction, bool bDisable = true);

    bool                               m_bHasEvents;
    bool                               m_bIteratingList;
    std::multimap<SString, CMapEvent*> m_EventsMap;
    std::list<CMapEvent*>              m_TrashCan;

    // Types for m_EventsMap access
    typedef std::multimap<SString, CMapEvent*>::const_iterator EventsConstIter;
    typedef std::multimap<SString, CMapEvent*>::iterator       EventsIter;
    typedef std::pair<EventsIter, EventsIter>                  EventsIterPair;
};
