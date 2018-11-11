CPPFLAGS= -I. -I/opt/opencv/include
CXXFLAGS= -Wall -Wextra -Werror
LDFLAGS = -Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
	-lopencv_imgcodecs

#modify DATA or VIEWER path command if not applicable
VIEWER= pvisu
DATA= ../data

OBJ= morphology.o
BIN= \
	make-se\
	dilation\
	erosion\
	opening\
	closing\
	labeling\
	difference\
	binarization

.PHONY: all
all: $(BIN)

$(BIN): morphology.o

.PHONY: test-deploy
test-deploy: all
	@./make-se ; true
	@./dilation ; true
	make extract-gear
	make extract-cell

.PHONY: extract-gear
extract-gear: all
	@echo "binarizating image: $(DATA)/gear.png";
	@./binarization 0 255 $(DATA)/gear.png gear.png > /dev/null;
	@echo "creating disk ...";
	@./make-se 2 10 disk.png > /dev/null;
	@echo "opening operation ...";
	@./opening disk.png gear.png circle.png > /dev/null;
	@echo "computing difference...";
	@./difference gear.png circle.png gear-res.png > /dev/null;
	@echo "labeling result...";
	@./labeling gear-res.png gear-labelled.png gear-res-color.png > /dev/null;
	@$(VIEWER) gear-res.png gear-res-color.png;


.PHONY: extract-cell
extract-cell:
	$(VIEWER) $(DATA)/cell.png;
	./labeling $(DATA)/cell-bin.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
