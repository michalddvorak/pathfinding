BUILD_DIR         = build
SRC_DIR           = src
EXE_DIR           = exe
CXXFLAGS         = -std=c++17 -Wall -pedantic -Wextra -g
DEPFLAGS         = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

MAIN_FILES       = $(shell grep -lr "int main" "./src/" | grep "cpp$$")
OTHER_FILES      = $(shell grep -Lr "int main" "./src/" | grep "cpp$$")

SOURCE_FILES     = $(MAIN_FILES) $(OTHER_FILES)
EXE_FILES        = $(MAIN_FILES:./src/%.cpp=./$(EXE_DIR)/%)
TEST_EXE_FILES   = $(filter %test, $(EXE_FILES))

OBJECT_FILES     = $(OTHER_FILES:./$(SRC_DIR)/%.cpp=./$(BUILD_DIR)/%.o)
DEP_FILES        = $(SOURCE_FILES:./$(SRC_DIR)/%.cpp=./$(BUILD_DIR)/%.d)




compile: $(EXE_FILES)



$(EXE_FILES) : ./$(EXE_DIR)/%: ./src/%.cpp $(OBJECT_FILES)
	@mkdir -p $$(dirname $@)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECT_FILES)


$(BUILD_DIR)/%.o : ./$(SRC_DIR)/%.cpp ./$(BUILD_DIR)/%.d
	@mkdir -p $$(dirname $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(EXE_DIR)


$(DEP_FILES):
include $(wildcard $(DEP_FILES))