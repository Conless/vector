test1() {
    cp tmp/data/one/code.cpp src/main.cpp
    bash scripts/build.sh
    time valgrind bin/vector_run >test.out
    diff test.out tmp/data/one/answer.txt
}

test2() {
    cp tmp/data/two/code.cpp src/main.cpp
    bash scripts/build.sh
    time valgrind bin/vector_run >test.out
    diff test.out tmp/data/two/answer.txt
}

test3() {
    cp tmp/data/three/code.cpp src/main.cpp
    bash scripts/build.sh
    time valgrind bin/vector_run >test.out
    diff test.out tmp/data/three/answer.txt
}

test4() {
    cp tmp/data/four/code.cpp src/main.cpp
    bash scripts/build.sh
    time valgrind bin/vector_run >test.out
    diff test.out tmp/data/four/answer.txt
}

test3
