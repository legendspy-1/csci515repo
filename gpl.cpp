/*
   gpl.cpp provides the main() function for the gpl interpreter

   Use C preprocessor symbols to turn on and off segments of code.

   SYM_TAB            assume that the symbol table exists
   GRAPHICS                open a window and show graphics

*/

#ifdef SYM_TAB
#include "Symbol.h"
#include "Symbol_table.h"
#include "Scope_man.h"
extern Scope_manager sm;
#endif

#include "error.h"

#ifdef GRAPHICS
#include <cassert>
#include "types_and_ops.h"
#include "Window.h"
#include "Constant.h"

std::unique_ptr<Window> window;

#endif

#include <iostream>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime> // for time()
#include <cstdio> // for fopen()

#ifdef P6
#include "Event_manager.h"
extern Event_manager em;
#endif
using namespace std;

extern int yylex();
extern int yyparse();

int yyerror(const char *str)
{
  gamelang::error(gamelang::PARSE_ERROR, str);
  return 1;
}

void illegal_usage(const char *qualifier = nullptr)
{
  cerr << "illegal command line argument(s)" << endl
    << "Usage:  $ gpl [-s seed] [-stdin] [-dump_pixels filename] filename[.gpl]" << endl;

  if (qualifier)
    cerr << qualifier << endl;

  exit(1);

}

bool dump_pixels = false;
char *dump_pixels_filename = 0;
bool graphics_flag = false;

// This function is called from window.cpp when the user quits the program
void user_quit_program()
{
#if defined P6
  cout << endl << "User quit program.  Executing termination blocks" << endl;
  em.execute_handlers(Window::TERMINATE);
#elif defined P4
  cout << endl << "User quit program. Printing the symbol table." << endl;
  cout << sm;
#endif

#ifdef GRAPHICS
  if (dump_pixels)
  {
    assert(graphics_flag);
    assert(window);

    window->dump_pixels(dump_pixels_filename);
  }
#endif
}

int main(int argc, char **argv)
{
  bool symbol_table_flag = false;

  // set local flags based on the command line argument when compiling gpl.cpp
  // (see comments in Makefile)
#ifdef SYM_TAB
  symbol_table_flag = true;
#endif

#ifdef GRAPHICS
  graphics_flag = true;
#endif


  extern FILE *yyin;
  char *filename = 0;
  int seed = time(0);
  bool read_keypresses_from_standard_input = false;

  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-stdin"))
      read_keypresses_from_standard_input = true;
    else if (!strcmp(argv[i], "-s"))
    {
      if (i+1 >= argc)
        illegal_usage();
      // make sure the argument after the -s is a number
      for (char *c = argv[i+1]; *c; c++)
      {
        if (!isdigit(*c))
        {
          cerr << "Illegal random number generator seed: "
            << argv[i+1]
            << endl;
          exit(1);
        }
      }
      seed = atoi(argv[i+1]);
      i += 1; // skip the seed value
    }
    else if (!strcmp(argv[i], "-dump_pixels"))
    {
      if (!graphics_flag)
        illegal_usage("Cannot dump the window using -dump_pixels unless graphics are enabled.");

      if (i+1 >= argc)
        illegal_usage();
      dump_pixels_filename = argv[i+1];
      dump_pixels = true;
      i += 1; // skip the dump filename
    }
    else
    {
      // can only specify one filename
      if (filename != 0)
        illegal_usage();

      filename = argv[i];
    }

  }
  if (!filename)
    illegal_usage();


  yyin = fopen(filename,"r");

  // if open failed, append .gpl to the filename and try again
  string string_filename=filename;
  if (!yyin)
  {
    string filename_with_extension=string_filename+".gpl";
    yyin = fopen(filename_with_extension.c_str(),"r");
  }

  // cannot open filename or filename+.gpl
  if (!yyin)
  {
    cerr << "Cannot open input file <" << filename << ">." << endl;
    return 1;
  }

  srand(seed);

  cout << "gpl.cpp::main()" << endl
    << "  input file(" << string_filename << ")" << endl
    << "  random seed(" << seed << ")" << endl
    << "  read_keypresses_from_standard_input" << "("
    << (read_keypresses_from_standard_input ? "true" : "false") << ")" << endl;

  if (dump_pixels)
    cout << "  dump_pixels(true, file = "  << dump_pixels_filename << ")"<< endl;
  else
    cout << "  dump_pixels(false)" << endl;

  cout << "  symbol_table("
    << (symbol_table_flag ? "true" : "false") << ")" << endl
    << "  graphics("
    << (graphics_flag ? "true" : "false") << ")" << endl << endl;

  cout << "gpl.cpp::main() Calling yyparse()" << endl << endl;

  int parse_result = yyparse();
  fclose(yyin);

  int yylex_destroy  (void);//gratuitous prototype
  yylex_destroy();
  cout << endl << "gpl.cpp::main() after call to yyparse()."<<endl<< endl;

  gamelang::starting_execution();


  // if -DGRAPHICS was specified when compiling gpl.cpp then include this code
#ifdef GRAPHICS
  int window_x;
  int window_y;
  int window_width;
  int window_height;
  double window_red;
  double window_green;
  double window_blue;
  string window_title;
  int animation_speed;

  // A user defining a reserved variable overrides the default value.
  // If the user defines the reserved variable with the incorrect type,
  // an error is generated.
  //
  //
  const int DEFAULT_WINDOW_X = 200;
  const int DEFAULT_WINDOW_Y = 200;
  const int DEFAULT_WINDOW_WIDTH = 500;
  const int DEFAULT_WINDOW_HEIGHT = 500;
  const double DEFAULT_WINDOW_RED = 1.0;
  const double DEFAULT_WINDOW_GREEN = 1.0;
  const double DEFAULT_WINDOW_BLUE = 1.0;
  const string DEFAULT_WINDOW_TITLE = "gpl window";
  const int DEFAULT_ANIMATION_SPEED = 88;

  Symbol* symbol;

  try { window_x=(symbol=sm.lookup("window_x")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_int() : DEFAULT_WINDOW_X; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_x", to_string(badtype), "int"); }

  try { window_y=(symbol=sm.lookup("window_y")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_int() : DEFAULT_WINDOW_Y; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_y", to_string(badtype), "int"); }

  try { window_width=(symbol=sm.lookup("window_width")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_int() : DEFAULT_WINDOW_WIDTH; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_width", to_string(badtype), "int"); }

  try { window_height=(symbol=sm.lookup("window_height")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_int() : DEFAULT_WINDOW_HEIGHT; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_height", to_string(badtype), "int"); }

  try { window_red=(symbol=sm.lookup("window_red")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_double() : DEFAULT_WINDOW_RED; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_red", to_string(badtype), "double"); }

  try { window_green=(symbol=sm.lookup("window_green")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_double() : DEFAULT_WINDOW_GREEN; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_green", to_string(badtype), "double"); }

  try { window_blue=(symbol=sm.lookup("window_blue")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_double() : DEFAULT_WINDOW_BLUE; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_blue", to_string(badtype), "double"); }

  try { window_title=(symbol=sm.lookup("window_title")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_string() : DEFAULT_WINDOW_TITLE; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "window_title", to_string(badtype), "string"); }

  try { animation_speed=(symbol=sm.lookup("animation_speed")) ? 
    std::unique_ptr<const Constant>(symbol->as_constant())->as_int() : DEFAULT_ANIMATION_SPEED; }
  catch(gamelang::Type badtype) { gamelang::error(gamelang::INVALID_TYPE_FOR_RESERVED_VARIABLE, "animation_speed", to_string(badtype), "int"); }

#endif


  if (parse_result != 0 || gamelang::num_errors() != 0)
  {
    // This is sent to cout instead of cerr so it
    // ends up in the .out files
    // It makes it easier to understand what happened when
    // reading the .out files
    cout << gamelang::num_errors() << " error";
    if (gamelang::num_errors() > 1)
      cout << "s";
    cout << " found."
      << endl
      << "gpl giving up."
      << endl;

    return(1);
  }

#ifndef GRAPHICS
  else
  {
    cout << "No errors found (parser probably worked correctly)."
      << endl
      << endl;
  }
#endif

#ifdef SYM_TAB
  if (parse_result == 0 && gamelang::num_errors() == 0)
  {
    cout << endl << "Printing the symbol table from main()" << endl;
    cout << sm;
  }
#endif

#ifndef GRAPHICS
  cout << "Graphics is turned off by the Makefile.  Program exiting."
    << endl << endl;
  cout << "gpl.cpp::main() done." << endl;
#else
  window = std::make_unique<Window>(window_x, window_y, window_width,
      window_height, window_title, animation_speed,
      window_red, window_green, window_blue,
      read_keypresses_from_standard_input
      );

  cout << "gpl.cpp::main() Calling window->initialize()." << endl << endl;
  window->initialize();

  cout << endl << "gpl.cpp::main() Passing control to window->main_loop()."
    << endl;

  // Tell glut to start the main event loop
  window->main_loop();
#endif
  return 0;
}
