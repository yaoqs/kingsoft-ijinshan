/********************************************************************
* CreatedOn: 2006-12-12   17:41
* FileName:  KDOMMacro.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KDOMMacro_H_
#define __KDOMMacro_H_

#include "KDOMBasic.h"
#include "KDOMAutoChild.h"


//////////////////////////////////////////////////////////////////////////
// ��Щ���Ѿ���֤���Լ��������������ռ�KANDOM
// ���Բ������������ռ�KANDOM�ڲ�ʹ����Щ��
//
// ע��,��Щ��ֻ����ȫ�����ֿռ���ʹ��

#define KDX_ENUM_DEFINE(_ENUM)\
	_KAN_DOM_BEGIN                                          \
	template<class _KDOMCursor>                             \
	inline long KXMLDataExchange(                           \
	_KDOMCursor& _domCur, _ENUM& _obj, bool _bWrite    \
	)                                                       \
	{                                                       \
		return KXMLDataExchange(_domCur, (unsigned int&)_obj, _bWrite);		\
	}\
	_KAN_DOM_END


#define KDX_BEGIN(_CLASS)                                   \
    _KAN_DOM_BEGIN                                          \
    template<class _KDOMCursor>                             \
    inline long KXMLDataExchange(                           \
        _KDOMCursor& _domCur, _CLASS& _obj, bool _bWrite    \
    )                                                       \
    {                                                       \
        int _nRetCode = -1;


//////////////////////////////////////////////////////////////////////////
// ���ڽ����͵�xml���л�
#define KDX_OBJ_NM(_NAME, _MEMBER_OBJ)                  \
        do {                                            \
            KDOMAutoChildEx<                            \
                _KDOMCursor                             \
            > domAutoChild(_NAME, &_domCur, _bWrite);   \
                                                        \
            _nRetCode = _domCur.ObjDataExchange(        \
                _bWrite, _obj._MEMBER_OBJ               \
            );                                          \
            if (FAILED(_nRetCode))                      \
            {                                           \
                return _nRetCode;                       \
            }                                           \
        } while (0)

#define KDX_OBJ_EX(_NAME, _MEMBER_OBJ, _DEFAULT)        \
        do {                                            \
            KDOMAutoChildEx<                            \
                _KDOMCursor                             \
            > domAutoChild(_NAME, &_domCur, _bWrite);   \
                                                        \
            _nRetCode = _domCur.ObjDataExchange(        \
                _bWrite, _obj._MEMBER_OBJ, _DEFAULT     \
            );                                          \
            if (FAILED(_nRetCode))                      \
            {                                           \
                return _nRetCode;                       \
            }                                           \
        } while (0)


#define KDX_END()                                       \
        return S_OK;                                    \
    }                                                   \
    _KAN_DOM_END






// �������������ֿռ��ڵ�ʱ��,ʹ������ĺ���� KDX_BEGIN/KDX_END

#define KDX_BEGIN_IN_NAMESPACE(_CLASS, PREV_NS) \
    };                                          \
    KDX_BEGIN(PREV_NS::_CLASS)

#define KDX_END_IN_NAMESPACE(PREV_NS)           \
    KDX_END();                                  \
    namespace PREV_NS {





#endif//__KDOMMacro_H_
