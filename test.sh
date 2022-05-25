#! /bin/bash

RED='\033[1;31m'
NC='\033[0m'
BLUE='\033[1;94m'
GREEN='\033[1;92m'
exec 2>/dev/null
printf "${BLUE}start test ${RED}\n"
make -s;
if [[ $(echo "ls" | tcsh) != $(echo "ls" | ./42sh) ]]; then
  echo "error at ls"
fi

if [[ $(echo "" | tcsh) != $(echo "" | ./42sh) ]]; then
  echo "error at empty"
fi

if [[ $(echo "not here" | tcsh) != $(echo "not here" | ./42sh) ]]; then
  echo "error at no command"
fi

if [[ $(echo "setenv lol ratio ; echo \$lol" | tcsh) != $(echo "setenv lol ratio ; echo \$lol" | ./42sh) ]]; then
  echo "error at env"
fi
##tmp
if [[ $(echo "                          ls                          -la" | tcsh) != $(echo "                          ls                          -la" | ./42sh) ]]; then
  echo "error at line formatting"
fi

if [[ $(echo "./tests/a.out" | tcsh) != $(echo "./tests/a.out" | ./42sh) ]]; then
  echo "error at segv"
fi

if [[ $(echo "ls -la ; ls ; echo \"lol\"" | tcsh) != $(echo "ls -la ; ls ; echo \"lol\"" | ./42sh) ]]; then
  echo "error at separator";
fi

if [[ $(echo "ls | grep a" | tcsh) != $(echo "ls | grep a" | ./42sh) ]]; then
  echo "error at simple pipe"
fi

if [[ $(echo "ls -la | grep r | cat -e | grep a" | tcsh) != $(echo "ls -la | grep r | cat -e | grep a" | ./42sh) ]]; then
  echo "error at advanced pipe"
fi

if [[ $(echo "echo \"foo\" > check ; cat check ; rm check" | tcsh) != $(echo "echo \"foo\" > check ; cat check ; rm check" | ./42sh) ]]; then
  echo "error at right redirections"
fi

if [[ $(echo "cat < test.sh" | tcsh) != $(echo "cat < test.sh" | ./42sh) ]]; then
  echo "error at left redirections"
fi

printf "${GREEN}end test\n"
printf "${NC}"
make fclean -s;