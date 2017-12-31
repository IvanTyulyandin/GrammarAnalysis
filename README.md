# GrammarAnalysis
Analysis of CFG (or RFA) and DFA

### How to build
For better performance run cmake at release mode:  
    cmake -DCMAKE_BUILD_TYPE=Release .
    
### Info
Each type of analysis (matrix, bottom up and GLL) contains Runner and Test. For example: to run Test (or Runner) for GLL go to folder GLL_Analysis after build and do ./GLL_AnalysisTest (./GLL_AnalysisRunner RecursiveFiniteAutomation DetermenisticFiniteAutomation for Runner)
