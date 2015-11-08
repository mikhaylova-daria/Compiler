//
// Created by Ава Катушка on 07.11.15.
//

#ifndef MINIJAVACOMPILER_TEMP_HPP
#define MINIJAVACOMPILER_TEMP_HPP

#include "../symbol/Symbol.h"
#include "../visitors/type_checking/SymbolTableBuilder.h"
#include <string>

namespace Temp {

	class CLabel {

	public:
		CLabel (CStorage& storage) {
			name = storage.Get(generatedNameStart + nextUniqueId);
		}

	    CLabel( const Symbol::CSymbol* symbol ) : name( name ) { }

	    const std::string& GetName() const {
		    name->GetName();
	    }

	private:

		const Symbol::CSymbol* name;
		static int nextUniqueId;
		static std::string generatedNameStart;

	};

}


#endif //MINIJAVACOMPILER_TEMP_HPP
