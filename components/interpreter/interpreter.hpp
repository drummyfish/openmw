#ifndef INTERPRETER_INTERPRETER_H_INCLUDED
#define INTERPRETER_INTERPRETER_H_INCLUDED

#include <map>
#include <stack>

#include "runtime.hpp"
#include "types.hpp"

namespace Interpreter
{
    class Opcode0;
    class Opcode1;
    class Opcode2;

    class Interpreter
    {
            std::stack<Runtime> mCallstack;
            bool mRunning;
            Runtime mRuntime;
            std::map<int, Opcode1 *> mSegment0;
            std::map<int, Opcode2 *> mSegment1;
            std::map<int, Opcode1 *> mSegment2;
            std::map<int, Opcode1 *> mSegment3;
            std::map<int, Opcode2 *> mSegment4;
            std::map<int, Opcode0 *> mSegment5;

            // not implemented
            Interpreter (const Interpreter&);
            Interpreter& operator= (const Interpreter&);

            void execute (Type_Code code);

            void abortUnknownCode (int segment, int opcode);

            void abortUnknownSegment (Type_Code code);

            void begin();

            void end();

        public:

            Interpreter();

            ~Interpreter();

            void installSegment0 (int code, Opcode1 *opcode);
            ///< Add segment 0 instruction (6b opcode, 24b argument).
            ///  Ownership of \a opcode is transferred to *this.

            void installSegment1 (int code, Opcode2 *opcode);
            ///< Add segment 1 instruction (6b opcode, 12b argument, 12b argument).
            ///  Ownership of \a opcode is transferred to *this.

            void installSegment2 (int code, Opcode1 *opcode);
            ///< Add segment 2 instruction (10b opcode, 20b argument).
            ///  Ownership of \a opcode is transferred to *this.

            void installSegment3 (int code, Opcode1 *opcode);
            ///< Add segment 3 instruction (18b opcode, 8b argument).
            ///  Ownership of \a opcode is transferred to *this.

            void installSegment4 (int code, Opcode2 *opcode);
            ///< Add segment 4 instruction (10b opcode, 8b argument, 8b argument).
            ///  Ownership of \a opcode is transferred to *this.

            void installSegment5 (int code, Opcode0 *opcode);
            ///< Add segment 5 instruction (26b opcode).
            ///  Ownership of \a opcode is transferred to *this.

            void run (const Type_Code *code, int codeSize, Context& context);
    };
}

#endif
