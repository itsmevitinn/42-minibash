# minibash
### Project overview:
This project consists of creating a shell that implements some of the functionalities present in bash.

The project was developed by [me](https://www.linkedin.com/in/itsmevitinn/) and [Gabriel Cardoso](https://www.linkedin.com/in/gabrielclcardoso/).

#### Features that will be implemented:
* Working prompt, with history;
* Search and launch executables by using the PATH variable or by using a relative or an absolute path;
* Handle closed single or double quotes;
* Handle the following redirections: `<` `<<` `>` `>>`;
* Handle pipes (`|` character);
* Handle environment variables (`$` character followed by their name);
* Handle `ctrl-C` `ctrl-D` and `ctrl-\`;
* Update the exit status of the commands;
* The following built-ins: 
1. `echo`(with option `-n`);
2. `cd`;
3. `pwd` `export` `unset` `exit`(with no options);
4. `env` (with no options or arguments).

#### Features that will NOT be implemented:
* Handling of unclosed quotes;
* handling of the following special characters: `\` `;` `||` `&&` `*`.

#
### Project approach:
In this project, we started by studying the bash program and how it behaved when using the features we were going to implement.
Afterwards, we divided the project into 6 parts:
* Prompt displaying;
* Input parsing;
* Signal handling;
* Environment variables;
* Built-in commands
* Command execution.

#### Prompt displaying:
For prompt displaying we used the readline function from the [GNU readline library](https://tiswww.case.edu/php/chet/readline/rltop.html#Documentation)
which has inumerous functionalities.
We used it to have a working history, handle `ctrl-D` and manipulate the prompt.

#### Input parsing:
Here is where we commited a mistake in the project approach. We decided to parse the prompt by doing string manipulation instead of tokenizing the words and symbols. This works fine, but it makes us loop through the input string several times manipulating different elements of the string each time, and it would also make it harder to add new symbols to be interpreted by the parser. If we were to do it again, we'd take the tokenization route.

#### Signal handling
The singal handling part was pretty straight forward. We used the [sigaction](https://linux.die.net/man/2/sigaction) function to create the handler for `ctrl-c`(SIGINT) and ignored `ctrl-\`(SIGQUIT). When handling the SIGINT signal we used some of the readline [functions](https://tiswww.case.edu/php/chet/readline/readline.html#Readline-Convenience-Functions) and [variables](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005freadline_005fstate). to manipulate the program behavior and the exit status value.

#### Environment variables:
For handling Environment variables we exported the [environ](https://linux.die.net/man/7/environ) variable and created a copy of it, this way we could manipulate the environment variables of our shell freely without messing with those of the shell that ran ours. We decided to copy it into a linked list so that it'd be easier to add, remove and change the contents of the environment variables.

#### Built-in commands:
The built-in commands were pretty straight foreward aswell, we read their documentation and implemented their behavior and error handling. For the built-ins that dealt with environment variables, we used the copy of [environ](https://linux.die.net/man/7/environ) that we created.

#### Command execution:
For the command execution we used function calls for the built-in commands and the [fork](https://linux.die.net/man/2/fork) function combined with the [execve](https://linux.die.net/man/2/execve) function for the executables. To implement the pipeline of commands we used the [pipe](https://linux.die.net/man/2/pipe) function and to extract the exit status of the child processes we used the status parameter of the [waitpid](https://linux.die.net/man/2/waitpid) function.

### Executing the program:

##### Platforms supported: Linux and Macos.
To try it out follow these simple steps:
#
#### Extra step for macos users:
If you are using macos you will need to install the readline library. You can do it through homebrew by runnig the following:
```
brew install readline
```
#

1 Clone this repository wherever you like:

```
git clone https://github.com/itsmevitinn/42-minibash.git
```
2 Enter the cloned repository and run make inside it:
```
cd 42-minibash && make
```
3 Run the minibash executable and prompt away :)
```
./minibash
```
