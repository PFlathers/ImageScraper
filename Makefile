#Compiler and Linker
CC 		:= g++

#The Target Binary
TARGET 		:= image_scraper.out 

#Flags, Libraries, and Includes
DEBUG 		:= -g
CFLAGS 		:= -Wall -c $(DEBUG)
LFLAGES 	:= -Wall $(DEBUG)
LIB 		:= -lcurl

#The Directories, Source, Includes, Objects, Binary, and Resources
BUILDDIR 	:= build
BINDIR 		:= bin
SRCDIR 		:= src
OBJEXT 		:= o
DEPEXT 		:= d
SRCEXT 		:= cpp


SOURCES 	:= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS 	:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))



all: directories $(TARGET)

remake: cleaner all

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR)

cleaner: clean
	@rm -rf $(BINDIR)

-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))


$(TARGET): $(OBJECTS)
	$(CC) -o $(BINDIR)/$(TARGET) $^ $(LIB)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
