//
// Created by Ава Катушка on 07.11.15.
//

#ifndef MINIJAVACOMPILER_FRAME_HPP
#define MINIJAVACOMPILER_FRAME_HPP

#include "../symbol/Symbol.h"
#include <vector>

namespace Frame {
	class IAccess {
	public:
		virtual ~IAccess();
	};

	class CFrame {
	public:
		CFrame( const Symbol::CSymbol* name, int formalsCount) {

		}

		int FormalsCount() const {
			// return formals.size();
		}

		const IAccess* Formal( size_t index) const {
			// return formals[index];
		}

	private:
		//vector<IAccess> formals;
	};
}


#endif //MINIJAVACOMPILER_FRAME_HPP
