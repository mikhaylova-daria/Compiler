//
// Created by Ава Катушка on 01.12.15.
//

#ifndef MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP
#define MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP

#include <assert.h>

template <class Target, class Visitor>
class CAcceptVisitor {
public:
	virtual void Accept(Visitor* visitor) {
		assert(visitor != nullptr);
		visitor->visit(static_cast<Target* const>(this));
	}

};


#endif //MINIJAVACOMPILER_TEMPLATE_VISITOR_HPP
