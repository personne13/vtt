CPPFLAGS=-I/opt/opencv/include -g
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
	-lopencv_imgcodecs
BIN=\
	median-filter\
	bilateral\
	nl-means\
	fourier

.PHONY: all
all: $(BIN)

.PHONY: test

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
