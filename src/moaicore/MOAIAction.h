// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIACTION_H
#define	MOAIACTION_H

#include <moaicore/MOAIBlocker.h>

//================================================================//
// MOAIAction
//================================================================//
/**	@brief Base class for actions.
*/
class MOAIAction :
	public MOAIBlocker {
private:
	
	bool	mNew;
	u32		mPass;
	
	MOAIAction* mParent;
	MOAIAction* mStackNext;
	USLeanLink < MOAIAction* > mLink;
	
	typedef USLeanList < MOAIAction* >::Iterator ChildIt;
	USLeanList < MOAIAction* > mChildren;
	
	//----------------------------------------------------------------//
	static int			_addChild				( lua_State* L );
	static int			_clear					( lua_State* L );
	static int			_isBusy					( lua_State* L );
	static int			_start					( lua_State* L );
	static int			_stop					( lua_State* L );

	//----------------------------------------------------------------//
	void				OnUnblock				();
	void				Update					( float step, u32 pass, bool checkPass );

protected:

	//----------------------------------------------------------------//
	virtual void		OnStart					();
	virtual void		OnStop					();
	virtual void		OnUpdate				( float step );
	
public:
	
	friend class MOAIActionMgr;
	
	DECL_LUA_DATA ( MOAIAction )
	
	//----------------------------------------------------------------//
	void				AddChild				( MOAIAction& action );
	void				ClearChildren			();
	bool				IsActive				();
	virtual bool		IsBusy					();
						MOAIAction				();
						~MOAIAction				();
	void				RegisterLuaClass		( USLuaState& state );
	void				RegisterLuaFuncs		( USLuaState& state );
	void				RemoveChild				( MOAIAction& action );
	void				Start					();
	void				Start					( MOAIAction& parent );
	void				Stop					();
	STLString			ToString				();
};

//================================================================//
// MOAIActionMgr
//================================================================//
class MOAIActionMgr :
	public USGlobalClass < MOAIActionMgr > {
private:

	static const u32 RESET_PASS	= 0xffffffff;

	u32 mPass;
	u32 mTotalPasses;

	MOAIAction mRoot;
	MOAIAction* mCurrentAction;

	//----------------------------------------------------------------//
	u32				GetNextPass				();

public:

	friend class MOAIAction;

	GET_SET ( MOAIAction*, CurrentAction, mCurrentAction )

	//----------------------------------------------------------------//
	void			Clear					();
	void			StartAction				( MOAIAction& action );
	void			Update					( float step );
					MOAIActionMgr			();
					~MOAIActionMgr			();
};

#endif