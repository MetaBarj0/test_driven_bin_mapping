# tdd_kata_bin_mapping

This is a kata, demonstrating how to perform real Test Driven Development on a
feature having a real business value. Each phase of the development will be
visible at a commit level.

## commit

Each commit will represent a single chronologically ordered 'unit' of work; an
incremental change in the project. That will allow to play at anytime with the
kata by seeing how the discipline is implemented by observing the differences
between two sibling commits.

# testing

This kata will demonstrate how Behavior Driven Development and Test Driven
Development can function together.

## BDD

The Behavior Driven Development part will be done by using the well known
`cucumber-cpp` toolset, that is an adaptor of the famous `cucumber` testing
framework designed for ``ruby``

### prerequisites

Steps described here apply well on a MacOS platform. Feel free to enrich this
file with other platform details is you will.

First, install ruby. on MacOS, using hombrew, it is quite simple :
`brew install ruby`

Then, ensure to install the `cucumber` gem.

_WARNING_ : due to a bug in the wire protocol in cucumber, make sure not to

install a 3.x version. 2.4.0 version of `cucumber` works well.

To install cucumber : `gem install cucumber -v 2.4.0`
Make sure everything is good by running : `cucumber --version`

Finally, install `cucumber-cpp` :
To install it on your mac : `brew install cucumber-cpp`

Feel free to visit https://github.com/cucumber/cucumber-cpp to see how it works

### running tests

A specific project named `behavior_tests` has been created under the `features`
sub directory.

To run tests, build this project, launch the produced executable that runs
silently in the background.

Then, change the current directory towards the root of this repository and
run : `cucumber`

Test output will display.

## TDD

The Test Driven Development part will be done by using the `googletest`
framework, the same as we use in our legacy products

The framework is added in the repository as a submodule in the folder
`googletest`

To synchronize it, change the current directory to the repository and run
`git submodule update --init`

### running tests

A specific project named `unit_tests` has been created under the src/tests
subdirectory.

It is a Qt autotest project so it is fully integrated into the IDE.
You can run tests by activating the test view in the left panel of the IDE.
