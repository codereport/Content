import pandas as pd 
# import cudf

mapping = {
    'GNU C++11'            : 'C++',
    'GNU C++14'            : 'C++',
    'GNU C++17'            : 'C++',
    'MS C++'               : 'C++',
    'MS C++ 2017'          : 'C++',
    'Clang++17 Diagnostics': 'C++',
    'Mono C#'              : 'C#',
    'Python 2'             : 'Python',
    'Python 3'             : 'Python',
    'PyPy 2'               : 'Python',
    'PyPy 3'               : 'Python',
    'GNU C11'              : 'C',
    'Java 8'               : 'Java',
    'Java 11'              : 'Java',
    'Node.js'              : 'JavaScript',
    'PascalABC.NET'        : 'Pascal',
    'Delphi'               : 'Pascal',
    'FPC'                  : 'Pascal'}

df = pd.read_csv('cf_ed_74.csv')

print(df.Lang
        .replace(mapping)
        .value_counts())
