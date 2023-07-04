%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

extern FILE* yyin;
extern int yylex(void);
void yyerror(char const *msg);

int line_num = 1;

char *identToken; // pass this pointer around to give token names to parser
int numberToken;
int count_names= 0;

unsigned int tempNum = 0;
unsigned int argNum = 0;
unsigned int loopNum = 0;
unsigned int ifNum = 0;
bool main_function_declared = false;


// 5/23/23 submission:
    // only need to handle arithmetic ops, array[], and function calls for now
    // no while() or if-else() blocks

enum Type {Integer, Array}; // the only types supported

struct Symbol {
  std::string name;
  Type type;
};

struct Function {       // program is a series of functions
    std::string name;
    std::vector<Symbol> declarations;
};

struct CodeNode {
    std::string code; // actual code generated as a string
    std::string name; // the name of an identifier, etc.
                        // use this to check for undeclared identifier errors
    std::string op_temp; // operation node with temp variables should populate this
};

std::vector<Function> symbol_table;

Function *get_function() {
  int last = symbol_table.size() - 1;
  if (last < 0) {
    printf("***Error. Attempt to call get_function with an empty symbol table\n");
    printf("Create a 'Function' object using 'add_function_to_symbol_table' before\n");
    printf("calling 'find' or 'add_variable_to_symbol_table'");
    exit(1);
  }
  return &symbol_table[last];
}

bool find_function(std::string &func_name) {

  if (symbol_table.empty()) {
    return false;
  }

  for (int i = 0; i < symbol_table.size() - 1; ++i) {
    if (symbol_table.at(i).name == func_name) {
      return true;
    }
  }
  
  return false;
}

bool check_same_type(std::string &value, Type t) {
  if (symbol_table.empty()) {
    printf("***Error. Symbol table is empty.\n");
    // Handle the error appropriately (e.g., return an error code, throw an exception, etc.)
    exit(1);
  }

  Function *f = get_function();
  for(int i = 0; i < f->declarations.size(); i++) {
    Symbol *s = &f->declarations[i];
    if (s->name == value) {
      if (s->type == t)
        return true;
    }
  }
  return false;
}

bool find(std::string &value) {
  if (symbol_table.empty()) {
    printf("***Error. Symbol table is empty.\n");
    // Handle the error appropriately (e.g., return an error code, throw an exception, etc.)
    return false;
  }

  Function *f = get_function();
  for(int i = 0; i < f->declarations.size(); i++) {
    Symbol *s = &f->declarations[i];
    if (s->name == value) {
      return true;
    }
  }
  return false;
}
void add_function_to_symbol_table(std::string &value) {
  Function f; 
  f.name = value; 
  symbol_table.push_back(f);

  Function* func = get_function();
  func->name = value;
}
void add_variable_to_symbol_table(std::string &value, Type t) {
  if (symbol_table.empty()) {
    printf("***Error. Symbol table is empty.\n");
    // Handle the error appropriately (e.g., return an error code, throw an exception, etc.)
    return;
  }

  Symbol s;
  s.name = value;
  s.type = t;
  Function *f = get_function();
  f->declarations.push_back(s);

  Symbol* sym = &(f->declarations.back());
  sym->name = value;
}

void print_symbol_table(void) {
  printf("symbol table:\n");
  printf("--------------------\n");
  for(int i=0; i<symbol_table.size(); i++) {
    printf("function: %s\n", symbol_table[i].name.c_str());
    for(int j=0; j<symbol_table[i].declarations.size(); j++) {
      printf("  locals: %s\n", symbol_table[i].declarations[j].name.c_str());
    }
  }
  printf("--------------------\n");
}


%}

%union {
  char *op_val;
  struct CodeNode *node; // pass this node ptr around, point it to appropriate tokens in CFGs
}

%define parse.error verbose
    
%token INTEGER ARRAY WHILE DO CONT BREAK READ WRITE IF THEN ELSE FUNCTION RETURN ADD SUB MULT DIV MOD LT GT LTE GTE NEQ EQ ASSIGN SEMICOLON COMMA LEFT_PAREN RIGHT_PAREN LEFT_SQR_BRACKET RIGHT_SQR_BRACKET BEGIN_BLOCK END_BLOCK COLON
    // these tokens have no attached semantic value
    // only leaves IDENT and NUMBER have intrinsic semantic value
      // the semantic values of leaves (numeric, integer values because it's what this language supports) are determined, and then passed up the syntax tree ^^

%token <op_val> IDENT       // identifiers and integers pass their name as a string up as their semantic value
%token <op_val> NUMBER

%type <node> function_ident
%type <node> prog_start
%type <node> functions
%type <node> function
%type <node> return
%type <node> arguments
%type <node> argument
%type <node> statements
%type <node> statement
%type <node> declaration
%type <node> declarations
%type <node> array_declaration
%type <node> function_call
%type <node> parameters
%type <node> param
%type <node> array_indexed
%type <node> assignment
%type <node> operand
%type <node> operator
%type <node> comparison_operator
%type <node> operation
%type <node> comparison_operation
%type <node> read_write
%type <node> if_then_else
%type <node> while
%type <node> keyword



    /* declare all tokens on above line */
%start prog_start
    /* specifies starting variable */
%%


    /* grammars go here */
prog_start: %empty 
            {
                CodeNode *node = new CodeNode;
                $$ = node;
            }
          | functions 
            {   
                
                if (main_function_declared == false) {
                  printf("ERROR! MIL expects a function named \"main\". exiting\n");
                  exit(1);
                }
                

                // this happens last.
                CodeNode *node = $1;
                std::string code = node->code;
                printf("Generated code:\n");
                printf("%s\n", code.c_str());
                
                print_symbol_table();



                /*
                printf("\n\nlast func: \"%s\"", symbol_table.at(symbol_table.size() - 1).name);

                std::string main_func = "main";
                if (!find_function(main_func)) { // need to make sure program contains a "main" function
                  printf("ERROR! MIL expects a function named \"main\".\n");

                  exit(1);
                }
                */

            }
          ;

functions: function
           {
              CodeNode *func = $1;
              std::string code = func->code;

              CodeNode *node = new CodeNode;
              node->code = code;
              $$ = node;
           }
         | function functions 
           {
              // $X in a macro for the attribute associated with a symbol at index X in the production rule
              CodeNode *func = $1; // points to first symbol attribute
              CodeNode *funcs = $2; // points to second symbol attribute
              std::string code = func->code + funcs->code; // appends the symbols
              
              CodeNode* node = new CodeNode;
              node->code = code; // point node to the new code
              $$ = node; // the semantic meaning of this entire expression is set to all the code built from its children
           }
         ;

function: FUNCTION INTEGER function_ident COLON arguments BEGIN_BLOCK declarations statements return END_BLOCK 
        {          
          argNum = 0; // reset the argNum for the next function to be parsed
          CodeNode* func_ident = $3;
  
          std::string code = "func " + func_ident->code + "\n";
          code += $5->code; // Append code from arguments
          code += $7->code; // Append code from declarations
          code += $8->code; // Append code from statements

          if (func_ident->code != "main") {
            code += $9->code; // Append code from return
          }
          code += "endfunc\n";

          CodeNode *node = new CodeNode;
          node->code = code;
          $$ = node;
        }
        ;

function_ident : IDENT 
                 {
                    // Add function declaration to symbol table
                    std::string func_name = $1;

                    if (symbol_table.empty() || !find_function(func_name)) { // if the function doesn't already exist, add it
                      add_function_to_symbol_table(func_name);
                    }

                    else if (find(func_name)) {
                      // might need an else branch for attmepts to declare function with non-unique name
                      printf("ERROR! by line %i attempting to declare function with non-unique identifier.\n", line_num);
                      exit(1);
                    }

                    if (func_name == "main") {
                      main_function_declared = true;
                    }

                    CodeNode* node = new CodeNode;
                    node->code = func_name;
                    $$ = node;
                 }

return: RETURN operation SEMICOLON 
        {
          // MIL format:
          // ret val
          CodeNode* op = $2;

          std::string code;

          if (!op->op_temp.empty()) { // if we passed along an operation with an attached temp
            code = op->code + "ret " + op->op_temp + "\n";
          }
          else {
            code = "ret " + op->code + "\n";
          }
        
          CodeNode *node = new CodeNode;
          node->code = code;
          $$ = node;
        }
      ;

arguments: %empty 
           {
            CodeNode *node = new CodeNode;
            $$ = node;
           }
         | argument
           { 
            CodeNode* arg = $1;
            std::string code = arg->code;

            CodeNode* node = new CodeNode;
            node->code = code;
            $$ = node;
           }
         | argument COMMA arguments 
           {
            CodeNode* arg = $1;
            CodeNode* args = $3;
            std::string code = arg->code + args->code;

            CodeNode* node = new CodeNode;
            node->code = code;
            $$ = node;
           }
         ;

argument: INTEGER IDENT 
          {
            // Add the newly encountered variable to the symbol table
            std::string var_name = $2;
            Type t = Integer;
            add_variable_to_symbol_table(var_name, t);

            // Generate the MIL code for the argument declaration
            std::string code = ". " + var_name + "\n";
            code += "= " + var_name + ", $" + std::to_string(argNum) + "\n"; // designate the position of the argument
            ++argNum;

            CodeNode* node = new CodeNode;
            node->code = code;
            $$ = node;
          }
        ;


statements: %empty 
            {
              CodeNode* node = new CodeNode;
              $$ = node;
            }
          | statement statements 
            {
              CodeNode* stmnt = $1;
              CodeNode* stmnts = $2;
              std::string code = stmnt->code + stmnts->code;

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
            }
          ;

statement: declaration SEMICOLON 
           {
              CodeNode* decl = $1;
              std::string code = decl->code;

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
           }
         | read_write SEMICOLON 
           {
              CodeNode* rw = $1;
              std::string code = rw->code;
              
              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
           }
         | assignment SEMICOLON 
           {
              CodeNode* assn = $1;
              std::string code = assn->code;

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
           }
         | function_call SEMICOLON
           {
              CodeNode* func_call = $1;
              std::string code = func_call->code;

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
           }
         | keyword SEMICOLON {} // don't need control keywords for now
         | if_then_else {printf("statement->if_then_else\n");}
         | while {printf("statement->while\n");}
          // 5/25/23 don't worry about if and while statements for now  
         ;

keyword: DO {printf("keyword->DO\n");}
       | CONT {
        std::string code = ":= beginloop" + std::to_string(loopNum) + "\n";
        CodeNode* node = new CodeNode;
        node->code = code;
        $$ = node;
    }
    | BREAK {
        std::string code = ":= endloop" + std::to_string(ifNum) + "\n";
        CodeNode* node = new CodeNode;
        node->code = code;
        $$ = node;
    }
       ;

declarations: %empty 
              {
                  CodeNode* node = new CodeNode;
                  $$ = node;
              }
            | declaration SEMICOLON declarations 
               {
                  CodeNode* decl = $1;
                  CodeNode* decls = $3;
                  std::string code = decl->code + decls->code;
                  
                  CodeNode* node = new CodeNode;
                  node->code = code;
                  $$ = node;
               }
            ;

declaration: INTEGER IDENT 
             {  
                // add newly declared variable to symbol table
                std::string var_name = $2;
                Type t = Integer;
                if (!find(var_name)) { // if the variable doesn't already appear in the symbol table, add it
                  add_variable_to_symbol_table(var_name, t);
                }

                else {
                  // variable name was already used in the current function
                  printf("ERROR! by line %i attempting to declare variable with non-unique identifier. exiting.\n", line_num);
                  exit(1);
                }

                std::string code = ". " + var_name + "\n";
                
                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
             }
          
           | array_declaration 
             {
                CodeNode* arr_decl = $1;
                std::string code = arr_decl->code;

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
             }
           ;

array_declaration: ARRAY LEFT_PAREN NUMBER RIGHT_PAREN LEFT_SQR_BRACKET INTEGER RIGHT_SQR_BRACKET IDENT 
                   {  
                      std::string arr_name = $8;
                      std::string n_elements = $3;

                      Type t = Array;
                      if (!find(arr_name)) {
                        add_variable_to_symbol_table(arr_name, t);
                      }
                      else {
                        printf("ERROR! by line %i attempting to declare array with non-unique identifer.\n", line_num);
                        exit(1);
                      }

                      if (std::stoi(n_elements) <= 0) {
                        printf("ERROR! by line %i attempting to declare array with size <= 0. exiting.\n", line_num);
                        exit(1);
                      }

                      std::string ident = arr_name;

                      std::string code = ".[] ";
                      code += ident + ", " + n_elements + "\n";

                      CodeNode* node = new CodeNode;
                      node->code = code;
                      $$ = node;
                   }
                 ;

function_call: IDENT LEFT_PAREN parameters RIGHT_PAREN 
               {
                  // MIL format
                    // call func_name, dest
                      // result of function call is stored in dest
                  
                  // call should store in temp, and temp should be assigned?
                  
                  std::string func_call = $1;
                  CodeNode* params = $3;

                  if (!find_function(func_call)) {
                    printf("ERROR! by line %i attempting to call undeclared function.\n", line_num);
    
                    exit(1);
                  }
                  
                  std::string temp = "temp_" + std::to_string(tempNum);
                  ++tempNum;
                
                  std::string code = params->code; // parameters // need to make sure parameters have newline attached
                  code += ". " + temp + "\n";      // temp declaration
                  code += "call " + func_call + ", " + temp + "\n"; // function call
                
                  CodeNode* node = new CodeNode;
                  node->code = code;
                  node->op_temp = temp;
                  $$ = node;
               }
             ;

parameters: param COMMA parameters 
            {
              CodeNode* param = $1;
              CodeNode* params = $3;
              std::string code = param->code + params->code;

              // don't think function call parameters should be added to symbol table, maybe check if a parameter is IN the symbol table when they're passed to a function call?

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
            }
          | param 
            {
              std::string code;
              CodeNode* param = $1;
              code = param->code;
              
              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
            }
          | %empty 
            {
              CodeNode* node = new CodeNode;
              $$ = node;
            }
          ;
param: operation
      {
        CodeNode* op = $1;
        std::string code;
        
        if (!op->op_temp.empty()) { // if an operation is being passes as parameter, do the operation then pass in the temp
          code = op->code + "param " + op->op_temp + "\n";
        }
        else {
          code = "param " + op->code + "\n";
        }
        
        // don't add params to symbol table

        CodeNode* node = new CodeNode;
        node->code = code;
        $$ = node;
      }
     ;

    /* arr[index] OR arr[123] are valid */
array_indexed: IDENT LEFT_SQR_BRACKET operation RIGHT_SQR_BRACKET 
             {
                // assign the array element to a temp to access
                // MIL format:
                  // =[] dest, src, index => dest = src[index]

                std::string temp = "temp_" + std::to_string(tempNum);
                ++tempNum;
                
                std::string arr_ident = $1;
                CodeNode* index = $3;

                if (!find(arr_ident)) {
                  printf("ERROR! by line %i attempting to access undeclared array. exiting.\n", line_num);
                  exit(1);
                }
                Type t = Array;
                if (!check_same_type(arr_ident, t)) {
                  printf("ERROR! by line %i attempting to access element of non-array type.\n", line_num);
                  exit(1);
                }

                std::string code = ". " + temp + "\n";  // declare temp
                code += "=[] " + temp + ", " + arr_ident + ", " + index->code + "\n";  // temp = arr[index]
            
                CodeNode* node = new CodeNode;
                node->code = code;
                node->op_temp = temp;
                $$ = node;
             }
             ;

assignment: IDENT ASSIGN operation 
            { // already declared variable assignment
                // MIL format
                  // a = 10 => a, 100
                    // rhs can be an immediate

                std::string lhs = $1;
                CodeNode* op = $3;

                std::string code;

                if (!find(lhs)) {
                  printf("ERROR! by line %i attempting to assign undeclared identifier. exiting.\n", line_num);
                  exit(1);
                }

                if (!op->op_temp.empty()) {
                  code = op->code + "= " + lhs + ", " + op->op_temp + "\n";
                }
                else {
                  code = "= " + lhs + ", " + op->code + "\n";
                }

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
            }
          | IDENT ASSIGN function_call
            { // adding this fixed function_call not passing temps through operations
                std::string lhs = $1;
                CodeNode* op = $3;
            
                std::string code;

                if (!find(lhs)) {
                  printf("ERROR! by line %i attempting to assign undeclared identifier. exiting.\n", line_num);
                }

                code = op->code + "= " + lhs + ", " + op->op_temp + "\n"; 

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;                
            }
          | IDENT LEFT_SQR_BRACKET operation RIGHT_SQR_BRACKET ASSIGN operation
            {  // for assigning array element
                // MIL format:
                  // []= arr, index, src => arr[index] = src;
                
                std::string arr_ident = $1;
                CodeNode* index = $3;
                CodeNode* rhs = $6;

                std::string code;

                if (!find(arr_ident)) {
                  printf("ERROR! by line %i attmepting to assign undeclared identifier. exiting.\n", line_num);
                }

                if (!rhs->op_temp.empty()) { // if the op had a temp
                  code = rhs->code + "[]= " + arr_ident + ", " + index->code + ", " + rhs->op_temp + "\n";
                }
                else {
                  code = "[]= " + arr_ident + ", " + index->code + ", " + rhs->code + "\n";
                }

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
            }
          | INTEGER IDENT ASSIGN operation 
            { // declaration assignment
                std::string var_name = $2;
                CodeNode* rhs = $4;
                
                if (!find(var_name)) {
                  Type t = Integer;
                  add_variable_to_symbol_table(var_name, t);
                }
                else {
                  printf("ERROR! by line %i attempting to declare variable with non-unique identifier. exiting\n", line_num);
                }

                // declaration
                std::string code = ". " + var_name;

                std::string lhs = var_name;

                // assignment

                if (!rhs->op_temp.empty()) { // if the op had a temp
                  code += rhs->code + "= " + lhs + ", " + rhs->op_temp + "\n";
                }
                else {
                  code += "= " + lhs + ", " + rhs->code + "\n";
                }
                
                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node; 
            }       
          ;


operand: IDENT 
         {
            std::string ident = $1;

            if (!find(ident)) {
              printf("ERROR! by line %i attempting to use undeclared identifier. exiting.\n", line_num);
              exit(1);
            }

            Type t = Integer;
            if (!check_same_type(ident, t)) {
              printf("ERROR! by line %i attempting to access array without specifiying index. exiting,\n", line_num);
              exit(1);
            }

            CodeNode* node = new CodeNode;
            node->code = ident;
            $$ = node;
         }
       | NUMBER 
         {
            std::string num = $1;

            CodeNode* node = new CodeNode;
            node->code = num;
            $$ = node;
         }
       | array_indexed 
         {
            CodeNode* arr_indexed = $1;
            std::string code = arr_indexed->code;
            std::string temp = arr_indexed->op_temp;

            CodeNode* node = new CodeNode;
            node->code = code;
            node->op_temp = temp;
            $$ = node;
         }
       | function_call
         {
            CodeNode* func_call = $1;
            std::string code = func_call->code;
            std::string temp = func_call->op_temp;

            CodeNode* node = new CodeNode;
            node->code = code;
            node->op_temp = temp;
            $$ = node;
         }
       ;


operator: ADD 
          {
              std::string code = "+";
              
              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
          }
        | SUB 
          {
              std::string code = "-";

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
          }
        | MULT 
          {
              std::string code = "*";

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
          }
        | DIV 
          {
              std::string code = "/";

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
          }
        | MOD 
          {
              std::string code = "%";

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
          }
        ;

    /* these operators will only ever be used in comparsisons */
comparison_operator: LT 
                     {
                        std::string code = "<";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   | GT 
                     {
                        std::string code = ">";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   | LTE 
                     {
                        std::string code = "<=";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   | GTE 
                     {
                        std::string code = ">=";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   | NEQ 
                     {
                        std::string code = "!=";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   | EQ 
                     {
                        std::string code = "==";

                        CodeNode* node = new CodeNode;
                        node->code = code;
                        $$ = node;
                     }
                   ;

operation: operation operator operation
           {
              std::string temp = "temp_" + std::to_string(tempNum);
              ++tempNum;

              // need some way to preserve the temp declaration, and operation, but return just the temp
              // create a pointer to the temp in ret statement, return just the temp?

              CodeNode* lhs = $1;
              CodeNode* op = $2;
              CodeNode* rhs = $3;

              std::string code;
              std::string temp_decl = ". " + temp + "\n";

              if (!lhs->op_temp.empty() && !rhs->op_temp.empty()) {
                code += temp_decl;
                code += lhs->code + rhs->code + op->code + " " + temp + ", " + lhs->op_temp + ", " + rhs->op_temp + "\n";
              }
              if (!lhs->op_temp.empty() && rhs->op_temp.empty()) { // if lhs has a temp
                code += temp_decl;
                code += lhs->code + op->code + " " + temp + ", " + lhs->op_temp + ", " + rhs->code + "\n"; 
              }
              else if (!rhs->op_temp.empty() && lhs->op_temp.empty()) { // if rhs has a temp
                code += temp_decl;
                code += rhs->code + op->code + " " + temp + ", " + lhs->code + ", " + rhs->op_temp + "\n";
              }
              else { // if neither op has a temp
                code += temp_decl;
                code += op->code + " " + temp + ", " + lhs->code + ", " + rhs->code + "\n";
              }

              CodeNode* node = new CodeNode;
              node->code = code;
              node->op_temp = temp;
              $$ = node;
           }
         | operand
           {
              CodeNode* op = $1;
              std::string code = op->code;
              std::string temp = op->op_temp;

              CodeNode* node = new CodeNode;
              node->code = code;
              node->op_temp = temp;
              $$ = node;
           }
         ;

         
    /*added this so that while and if only allows comparisons*/
    /* new ensures that all operands inc. function calls can be on either side of a comparsion statement */
comparison_operation: operation comparison_operator operation 
                      {
                          // MIL format:
                          // != dest, src1, src2 => dest = src1 != src2

                          /*
                          // MIL code should look like this:
                            . temp_tempNum
                            != temp_tempNum, src1, src2
                          */
                          
                          std::string temp = "temp_" + std::to_string(tempNum);
                          ++tempNum;

                          // need some way to preserve the temp declaration, and operation, but return just the temp
                          // create a pointer to the temp in ret statement, return just the temp?

                          CodeNode* lhs = $1;
                          CodeNode* op = $2;
                          CodeNode* rhs = $3;
                          std::string code = ". " + temp + "\n"; // declare the temp

                          // do the operation on the next line
                          
                          if (!lhs->op_temp.empty() && !rhs->op_temp.empty()) {
                            code += op->code + " " + temp + ", " + lhs->op_temp + ", " + rhs->op_temp + "\n";
                          }
                          if (!lhs->op_temp.empty() && rhs->op_temp.empty()) { // if lhs has a temp
                            code += op->code + " " + temp + ", " + lhs->op_temp + ", " + rhs->code + "\n"; 
                          }
                          else if (!rhs->op_temp.empty() && lhs->op_temp.empty()) { // if rhs has a temp
                            code += op->code + " " + temp + ", " + lhs->code + ", " + rhs->op_temp + "\n";
                          }
                          else { // if neither op has a temp
                            code += op->code + " " + temp + ", " + lhs->code + ", " + rhs->code + "\n";
                          }

                          CodeNode* node = new CodeNode;
                          node->code = code;
                          node->op_temp = temp;
                          $$ = node;     
                      }
                    ;
                    
read_write: READ LEFT_PAREN IDENT RIGHT_PAREN
            { 
              // MIL format:
                // .< dest => read(dest) // read a value into variable "dest" from std in
          
                std::string dest = $3;

                if (!find(dest)) {
                  printf("ERROR! by line %i attempting to read into undeclared identifier. exiting.\n", line_num);
                  exit(1);
                }

                std::string code = ".< " + dest + "\n";

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;

            }
          | READ LEFT_PAREN IDENT LEFT_SQR_BRACKET operation RIGHT_SQR_BRACKET RIGHT_PAREN 
            { // dest is an arr[index]
              // MIL format:
                // .[]< dest, index => read(dest[index])

                std::string dest = $3;
                CodeNode* index = $5;

                if (!find(dest)) {
                  printf("ERROR! by line %i attempting to read into undeclared identifier. exiting.\n", line_num);
                  exit(1);
                }
                
                std::string code = ".[]< " + dest + ", " + index->code + "\n";

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
                
            }
          | WRITE LEFT_PAREN operation RIGHT_PAREN 
            { // might need to modify this rule so that it can only write variables
                // MIL format:
                  // .> src => write(src) // write the value of src to std out
                
                CodeNode* src = $3;
                std::string code = ".> " + src->code + "\n";

                CodeNode* node = new CodeNode;
                node->code = code;
                $$ = node;
            }
          | WRITE LEFT_PAREN IDENT LEFT_SQR_BRACKET operation RIGHT_SQR_BRACKET RIGHT_PAREN
            {
              // MIL format:
                // .[]> src, index => write(src[index]) // write value of array element src[index] to std out

              std::string src = $3;
              CodeNode* index = $5;

              if (!find(src)) {
                printf("ERROR! by line %i attempting to print undeclared identifier. exiting.\n", line_num);
                exit(1);
              }
  
              std::string code = ".[]> " + src + ", " + index->code + "\n";

              CodeNode* node = new CodeNode;
              node->code = code;
              $$ = node;
            }
          ;

if_then_else: IF LEFT_PAREN comparison_operation RIGHT_PAREN THEN BEGIN_BLOCK statements END_BLOCK {
        printf("IF LEFT_PAREN comparison_operation RIGHT_PAREN THEN BEGIN_BLOCK statements END_BLOCK\n");
        CodeNode* comparison = $3;
        CodeNode* if_statements = $7;

        std::string code;

        
        std::string ifElseLabel = std::to_string(ifNum);
        std::string numT = std::to_string(tempNum);
        
        code = comparison->code;                               
        code += "?:= if_true" + ifElseLabel + ", " + comparison->op_temp + "\n";  
        code += ":= endif" + ifElseLabel + "\n";                   
        code += ": if_true" + ifElseLabel + "\n";                  
        code += if_statements->code;  
        code += ": endif" + ifElseLabel + "\n";                          
        

        CodeNode* node = new CodeNode;
        node->code = code;
        $$ = node;

        ++tempNum;
        ++ifNum;
    }
    | IF LEFT_PAREN comparison_operation RIGHT_PAREN THEN BEGIN_BLOCK statements END_BLOCK ELSE BEGIN_BLOCK statements END_BLOCK {
        printf("if_then_else->IF LEFT_PAREN comparison_operation RIGHT_PAREN THEN statement ELSE statement\n");
        CodeNode* comparison = $3;
        CodeNode* if_statements = $7;
        CodeNode* else_statements = $11;

        std::string code;

        // Generate a unique label for the if-else statement
        std::string ifElseLabel = std::to_string(ifNum);
        std::string numT = std::to_string(tempNum);

        // Construct the if-else statement code
        code = comparison->code;                                
        code += "?:= if_true" + ifElseLabel + ", " + comparison->op_temp + "\n";  
        code += ":= else" + ifElseLabel + "\n";                   
        //code += ":= endif" + ifElseLabel + "\n";                   
        code += ": if_true" + ifElseLabel + "\n";                 
        code += if_statements->code;                          
        code += ":= endif" + ifElseLabel + "\n";                
        //code += ": else" + ifElseLabel + "\n";                 
        code += else_statements->code; 
        code += ": endif" + ifElseLabel + "\n";                         

        CodeNode* node = new CodeNode;
        node->code = code;
        $$ = node;

        ++tempNum;
        ++ifNum;
    }
    ;



      /*while*/
while:
  WHILE LEFT_PAREN comparison_operation RIGHT_PAREN DO BEGIN_BLOCK statements END_BLOCK
  {
   //printf("while->WHILE LEFT_PAREN comparison_operation RIGHT_PAREN DO BEGIN_BLOCK statements END_BLOCK\n");
    CodeNode* comparison = $3;
    CodeNode* loop_statements = $7;

    std::string code;

    //generate a unique label for the loop
    std::string loopLabel = std::to_string(loopNum);
    std::string numT = std::to_string(tempNum);

    //construct the while loop code
    code = ": beginloop" + loopLabel + "\n";                 //label for the start of the loop
    code += comparison->code;                                //code for the comparison operation
    code += "?:= loopbody" + loopLabel + ", " + comparison->op_temp + "\n";  //branch to loop body if comparison is true
    code += ":= endloop" + loopLabel + "\n";                   //label for the end of the loop
    code += ": loopbody" + loopLabel + "\n";                  //label for the loop body
    code += loop_statements->code;                            //code for the loop statements
    code += ":= beginloop" + loopLabel + "\n";                //jump back to the start of the loop
    code += ": endloop" + loopLabel + "\n";                   //label for the end of the loop

    CodeNode* node = new CodeNode;
    node->code = code;
    $$ = node;

    ++loopNum;
    ++tempNum;  //increment the temporary number for the next loop
  }
;





%%

void yyerror(char const *s) {
   fprintf (stderr, "Error at line %d: %s\n", line_num, s);
   exit(1);
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        return 1;
    }
    yyin = input_file;
    yyparse();
    fclose(input_file);

    return 0;
}
