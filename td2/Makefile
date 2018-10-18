CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	color-convert\
	hsv-modification\
	eq-histogram\
	adaptative-th\
	otsu

.PHONY: all
all: $(BIN)

.PHONY: test

test:
	./hsv-modification 100 0 0 ../data/horse.png horse-hsv.png


.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
