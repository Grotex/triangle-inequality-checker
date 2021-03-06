#ifndef constants_hpp
#define constants_hpp

#include <string>

using namespace std;

const string REGEX_LHS_LEQ_RHS      = "(.*)\\s*<=\\s*(.*)";
const string REGEX_LHS_GEQ_RHS      = "(.*)\\s*>=\\s*(.*)";
const string REGEX_LHS_EQ_RHS       = "([kmnpquvwxyzt]{1}[0-9]?|P)\\s*=\\s*(.*)";
const string REGEX_INIT_FUNCTIONS   = "void init_(.*)\\(\\);";
const string REGEX_TRIANGLE_VAR     = "(?!sqrt\\b|long_d\\b|t\\b|"
                                      "sum\\b|prod\\b|pow\\b|max\\b|min\\b|"
                                      "sin\\b|cos\\b|asin\\b|acos\\b|pi\\b)\\b"
                                      "[a-zA-Z]+([0-9]?)+[A-Z]?";
const string REGEX_REMARKABLE_DIST  = "[FGHINOK]{2}";
const string REGEX_CYCLIC_SUM       = "\\[sum (?!sum)([^\\[\\]]*)\\]";
const string REGEX_CYCLIC_PROD      = "\\[prod (?!prod)([^\\[\\]]*)\\]";

const string INPUT_FILE             = "inequality.txt";
const string COMMENT_STR            = "//";
const string END_OF_INPUT_DELIMITER = "---";
const string MEMBER_FUNC_PTR_KEY    = "__POINTERS_TO_MEMBER_FUNCTIONS__";
const string TRIANGLE_ELEM_MAP_KEY  = "__MAP_OF_TRIANGLE_ELEMENTS_TO_POINTERS__";
const string INDENT                 = string(12, ' ');

const char DELIMITER                = '_';


#endif /* constants_hpp */
