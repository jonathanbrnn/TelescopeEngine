#include "Grid.h"

int GetRandomInt(int a, int b) {
    random_device rd; 
    mt19937 gen(rd());

    uniform_int_distribution<> distr(a, b);

    return distr(gen); 
}

void Grid::SetCellThreshold(int cell_threshold) {
    if (cell_threshold < 2) {
        common_divisor = 2; 
        cout << "GRID: WARNING! cell_threshold cannot be smaller than 2. common_divisor has been set to 2." << endl; 
        return; 
    }
    if (!cell_threshold_set) {
        this->cell_threshold = cell_threshold; 
        cell_threshold_set = true; 
    }
    else {
        cout << "GRID: WARNING! cell_threshold cannot be set twice!" << endl; 
    }
}

InputManager* input; 

void Grid::Start() {
    screen_width = managerHub->Get_Screen_Width(); 
    screen_height = managerHub->Get_Screen_Height(); 

    input = managerHub->inputManager; 

    for (int i = cell_threshold - 1; i > 2; i--) {
        if (screen_width % i == 0 && screen_height % i == 0) {
            common_divisor = i; 
            break; 
        }
    }

    if (common_divisor == -1) {
        cout << "GRID: WARNING! No common divisor found under: " << cell_threshold << "." << endl; 
        return; 
    }

    SDL_Renderer* renderer = managerHub->renderer->Get_Renderer(); 


    vector<string> cell_filepaths = {"../media/images/cell_state0.png", "../media/images/cell_state1.png"}; 



    for (int i = 0; i < static_cast<int>(screen_height / common_divisor); i++) {
        vector<Cell*> current_row;
        vector<int> current_row_bin;  

        for (int j = 0; j < static_cast<int>(screen_width / common_divisor); j++) {
            Cell* current_cell = new Cell("cell" + to_string(i) + to_string(common_divisor + j), common_divisor * j, common_divisor * i, 0, common_divisor, common_divisor, 0);
            
            managerHub->entityManager->AddNewObject(current_cell);
            
            current_row.push_back(current_cell); 
            current_row_bin.push_back(0); 
        }

        cells.push_back(current_row); 
        cells_bin.push_back(current_row_bin); 
    }
}

void Grid::Update() {
    if (input->IsPressed("Space")) {
        is_paused = !is_paused; 
    }

    static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int rows = cells_bin.size(); 
    int cols = cells_bin[0].size(); 

    if (!is_paused) {
        current_frame += 1;
        if (current_frame > frame_delay) { current_frame = 0; }

        if (current_frame >= frame_delay) {
            vector<vector<int>> bin_copy = cells_bin; 

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int live_neighbours = 0; 

                    for (int d = 0; d < 8; d++) {
                        int ni = i + dx[d]; 
                        int nj = j + dy[d]; 

                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            live_neighbours += bin_copy[ni][nj]; 
                        }
                    }

                    if (bin_copy[i][j] == 1) {
                        if (live_neighbours == 2 || live_neighbours == 3) { 
                            cells_bin[i][j] = 1; 
                            cells[i][j]->SetState(1); 
                        }
                        else { 
                            cells_bin[i][j] = 0; 
                            cells[i][j]->SetState(0); 
                        }
                    }
                    else if (live_neighbours == 3) {
                        cells_bin[i][j] = 1; 
                        cells[i][j]->SetState(1); 
                    }
                }
            }
        }
    }
    else if (input->IsPressed("Mouse Left") || input->IsPressed("Mouse Right")) {
        int mouse_x; 
        int mouse_y; 

        input->GetMousePosition(mouse_x, mouse_y); 

        int i = static_cast<int>(mouse_y / common_divisor); 
        int j = static_cast<int>(mouse_x / common_divisor);

        // Either remove FlipState() or make it return the new state to instantly do both (could be: cells_bin[i][j] = cells[i][j]->FlipState(); )
        if (cells_bin[i][j] == 1) { 
            cells_bin[i][j] = 0; 
            cells[i][j]->FlipState(); 
        }
        else { 
            cells_bin[i][j] = 1; 
            cells[i][j]->FlipState(); 
        }
    }

    if (input->IsPressed("Up")) { 
        frame_delay--; 
        if (frame_delay < 0) { frame_delay = 0; }
        cout << "GRID: Frames between generations: " << frame_delay << endl; 
    }
    if (input->IsPressed("Down")) { 
        frame_delay++;
        cout << "GRID: Frames between generations: " << frame_delay << endl; 
    }
}