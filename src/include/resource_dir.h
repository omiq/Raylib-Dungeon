#ifndef RESOURCE_DIR_H
#define RESOURCE_DIR_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

// Resources are now always in the same directory as the executable
#define RESOURCE_PATH "resources/"

// Search for the resources directory and set it as the current working directory
static int SearchAndSetResourceDir(const char* resourceDir) {
    char currentPath[PATH_MAX];
    char testPath[PATH_MAX];
    
    // Get the current working directory
    if (getcwd(currentPath, sizeof(currentPath)) == NULL) {
        printf("Error getting current directory\n");
        return 0;
    }

    printf("Current working directory: %s\n", currentPath);

    // Try the current directory first
    snprintf(testPath, sizeof(testPath), "%s/%s", currentPath, resourceDir);
    printf("Trying resource path: %s\n", testPath);
    
    if (access(testPath, F_OK) == 0) {
        printf("Found resources at: %s\n", testPath);
        return 1;
    }

    printf("Error: Could not find resources directory at %s\n", testPath);
    return 0;
}

// Helper function to build resource path
static void GetResourcePath(const char* filename, char* outPath, size_t outPathSize) {
    snprintf(outPath, outPathSize, "%s%s", RESOURCE_PATH, filename);
    printf("Loading resource: %s\n", outPath);
}

#endif // RESOURCE_DIR_H 