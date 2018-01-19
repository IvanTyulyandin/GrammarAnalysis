GrammarAnalysis:


How to build:

Script buildAndTest.sh will build and run test for all algorithms:

    chmod +x buildAndTest.sh
    ./buildAndTest.sh

If you don't want to run tests:

    cmake -DCMAKE_BUILD_TYPE=Release .
    make -j (numberOfThreads)

-------------------------------------------------------------------------

Info:

Each type of analysis (matrix, bottom up and GLL) contains Runner and Test.

How to use Runner (for example, matrixAnalysisRunner):
    cd matrixAnalysis
    ./matrixAnalysisRunner ChomskyFormGrammar DeterministicFiniteAutomata

    Examples of DeterministicFiniteAutomata are in folder testDFA
    Examples of ChomskyFormGrammar are in folder testGrammars

Args for bottomUpAnalysisRunner and GLL_AnalysisRunner:
    1: RecursiveFiniteAutomata (examples of automata are in folder testRFA)
    2: DeterministicFiniteAutomata

How to use Test (for example, bottomUpAnalysisTest):
    cd bottomUpAnalysis
    ./bottomUpAnalysisTest

