//
// Created by Ава Катушка on 01.12.15.
//

#ifndef MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP
#define MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP

#include <assert.h>

template <class Target, class Visitor, class Base>
class CAcceptVisitor : public Base {
public:
	virtual void Accept(Visitor* visitor) {
		assert(visitor != nullptr);
		visitor->Visit(static_cast<Target* const>(this));
	}

};

template <class Visitor>
class IAcceptVisitor  {
public:
    virtual void Accept(Visitor* visitor) = 0;

};


#endif //MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP
