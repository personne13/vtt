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
	binarization\
	add-boundary\
	median-filter\
	bilateral

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
	#./bilateral 10 30 $(DATA)/cell.png cellbb.png
	#./binarization 0 255  cellbmf.png cellb.png
extract-cell: all
	./make-se 2 10 disk.png
	./opening disk.png $(DATA)/cell.png cell_opened.png
	./binarization 100 255 cell_opened.png cell_opened_bin.png
	./median-filter 7 cell_opened_bin.png cell-res.png
	./labeling cell-res.png cell-r.png cell-res-color.png
	./make-se 1 2 diamond.png
	./erosion diamond.png cell-res.png erosion.png
	./dilation diamond.png cell-res.png dilation.png
	./difference dilation.png erosion.png cell-res-boundary.png
	./binarization 0 255 cell-res-boundary.png cell-res-boundary-bin.png
	./add-boundary $(DATA)/cell.png cell-res-boundary-bin.png cell-final.png
	$(VIEWER) $(DATA)/cell.png cell-res-boundary.png cell-res-color.png cell-final.png cell-res.png


.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
