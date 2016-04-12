#include "gtest/gtest.h"
#include <thread>
#include <pthread.h>

#include <errno.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


TEST( CorrectProgramm, Factorial
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	char command [90]= "../../Compiler/programms/factorial.mj";
	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}

TEST( CorrectProgramm, BinarySearch
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}

	char command[90] = "../../Compiler/programms/binary_search.mj";

	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}

TEST( CorrectProgramm, BinaryTree
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}

	char command[90] = "../../Compiler/programms/binary_tree.mj";

	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}


TEST( CorrectProgramm, BubbleSort
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	const char* command = "../../Compiler/programms/bubble_sort.mj";

	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}


TEST( CorrectProgramm, LinearSearch
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	const char* command = "../../Compiler/programms/linear_search.mj";
	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}


TEST( CorrectProgramm, LinkedList
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	const char* command = "../../Compiler/programms/linked_list.mj";
	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}
TEST( CorrectProgramm, QuickSort
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	const char* command = "../../Compiler/programms/quick_sort.mj";
	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}

TEST( CorrectProgramm, TreeVisitor
) {
	char path_exe[90] = "../../Compiler/bin/mjc ";
	char** argv = new char*[2];
	argv[0] = (char*)malloc(sizeof(char)*strlen(path_exe));
	for (int i = 0; i < strlen(path_exe); ++i) {
		argv[0][i] = path_exe[i];
	}
	const char* command = "../../Compiler/programms/tree_visitor.mj";
	argv[1] = (char*) malloc(sizeof(char) * strlen(command));
	for (int i = 0; i < strlen(command); ++i) {
		argv[1][i] = command[i];
	}

	FILE* stream = popen(strcat(path_exe, command),"r");
	int return_code = pclose(stream);
	EXPECT_EQ( 0, return_code );

}