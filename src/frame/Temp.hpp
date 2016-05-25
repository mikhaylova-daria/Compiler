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
			name = storage.Get(generatedNameStart + std::to_string(nextUniqueId++));
		}

	    CLabel( const Symbol::CSymbol* symbol ) : name( symbol ) { }

	    const std::string& GetName() const {
		    return name->GetName();
	    }

	private:

		const Symbol::CSymbol* name;
		static int nextUniqueId;
		static std::string generatedNameStart;

	};

    class CTemp {

    public:
        CTemp (CStorage& storage) {
	        name = storage.Get(generatedNameStart + std::to_string(nextUniqueId++));
        }

        CTemp( const Symbol::CSymbol* symbol ) : name( symbol ) { }

        const std::string& GetName() const {
	        return name->GetName();
        }

		bool operator==(const CTemp& other) const { return name == other.name; }
        bool operator<(const CTemp& other) const { return name < other.name; }
        bool operator!=(const CTemp& other) const { return !(*this == other);}

    private:

        const Symbol::CSymbol* name;
        static int nextUniqueId;
        static std::string generatedNameStart;

    };

    class CTempCompare {
    public:
        bool operator()(const CTemp* lhs, const CTemp* rhs) const { return *lhs < *rhs; }
    };

	typedef std::shared_ptr<CTemp> CTempPtr;

}


#endif //MINIJAVACOMPILER_TEMP_HPP
