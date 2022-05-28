BUILDDIR         = build
SRCDIR           = src
CXXFLAGS         = -std=c++17 -Wall -pedantic -Wextra -g
DEPFLAGS         = -MT $@ -MMD -MP -MF $(BUILDDIR)/$*.d
PROG             = pathfinding
SRCFILES         = $(shell find $(SRCDIR) -name "*.cpp")
OBJS             = $(SRCFILES:%.cpp=./$(BUILDDIR)/%.o)
DEPS             = $(SRCFILES:%.cpp=./$(BUILDDIR)/%.d)


compile: $(PROG)

$(PROG) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS)

$(BUILDDIR)/%.o : %.cpp $(BUILDDIR)/%.d
	@mkdir -p $$(dirname $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(PROG)

$(DEPS):
include $(wildcard $(DEPS))