src/VT100_KJ_erase_commands.c:		memset(&grid->screen[grid->y][grid->x], ' ',
src/VT100_KJ_erase_commands.c:			(grid->width - grid->x) + ((grid->height - grid->y) * grid->width));
src/VT100_KJ_erase_commands.c:		memset(grid->screen[0], ' ', 
src/VT100_KJ_erase_commands.c:			(grid->width - grid->x) + ((grid->height - grid->y) * grid->width));
src/VT100_KJ_erase_commands.c:		memset(grid->screen[0], ' ',
src/VT100_KJ_erase_commands.c:			grid->width * grid->height);
src/VT100_KJ_erase_commands.c:	new_render_op(grid, ERASE_DISPLAY, grid->x, grid->y);
src/VT100_KJ_erase_commands.c:	grid->full_redraw = true;
src/VT100_KJ_erase_commands.c:		memset(&grid->screen[grid->y][grid->x], ' ', grid->width - grid->x);
src/VT100_KJ_erase_commands.c:		memset(grid->screen[grid->y], ' ', grid->x + 1);
src/VT100_KJ_erase_commands.c:		memset(grid->screen[grid->y], ' ', grid->width);
src/cursor_handling.c:		(grid->x * x11->tile_width) + x11->margin,
src/cursor_handling.c:		(grid->y * x11->tile_height) + x11->tile_height,
src/cursor_handling.c:		&grid->screen[grid->y][grid->x],
src/cursor_handling.c:		(grid->x * x11->tile_width) + x11->margin,
src/cursor_handling.c:		(grid->y * x11->tile_height) + x11->tile_height,
src/cursor_handling.c:		&grid->screen[grid->y][grid->x],
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_printable;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_vertical_tab;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_carriage_return;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_newline;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_tab;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_backspace;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = parse_escape_code;
src/init_function_pointer_arrays.c:			grid->grid_functions[i] = grid_nothing;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = A_cursor_up;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = C_cursor_forward;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = H_cursor_movement;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = J_erase_display;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = K_erase_line;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = P_delete_character;
src/init_function_pointer_arrays.c:			grid->command_functions[i] = command_nothing;
src/init_function_pointer_arrays.c:	grid->render_operation_functions[PRINTABLE] = render_printable;
src/init_function_pointer_arrays.c:	grid->render_operation_functions[ERASE_DISPLAY] = full_redraw;
src/init_function_pointer_arrays.c:	grid->render_operation_functions[ERASE_LINE] = render_line_erasing;
src/init_function_pointer_arrays.c:	grid->render_operation_functions[DELETE_CHARACTER] = render_character_deletion;
src/init_grid.c:	total_size += (sizeof(char *) * grid->height);
src/init_grid.c:	total_size += (sizeof(char) * grid->height * grid->width);
src/init_grid.c:	total_size += (sizeof(int *) * grid->height * 2);
src/init_grid.c:	total_size += (sizeof(int) * grid->height * grid->width * 2);
src/init_grid.c:	current = grid->chunk;
src/init_grid.c:	grid->screen = current;
src/init_grid.c:	current += (sizeof(char *) * grid->height);
src/init_grid.c:	while (i < grid->height) {
src/init_grid.c:		grid->screen[i] = current;
src/init_grid.c:		current += (sizeof(char) * grid->width);
src/init_grid.c:	grid->fg_colors = current;
src/init_grid.c:	current += (sizeof(int *) * grid->height);
src/init_grid.c:	while (i < grid->height) {
src/init_grid.c:		grid->fg_colors[i] = current;
src/init_grid.c:		current += (sizeof(int) * grid->width);
src/init_grid.c:	grid->bg_colors = current;
src/init_grid.c:	current += (sizeof(int *) * grid->height);
src/init_grid.c:	while (i < grid->height) {
src/init_grid.c:		grid->bg_colors[i] = current;
src/init_grid.c:		current += (sizeof(int) * grid->width);
src/init_grid.c:	memset(grid->screen[0], ' ', sizeof(char) * grid->width * grid->height);
src/init_grid.c:	memset(grid->bg_colors[0], 0, sizeof(int) * grid->width *grid->height);
src/init_grid.c:	while (i < grid->height) {
src/init_grid.c:		while (j < grid->width) {
src/init_grid.c:			grid->fg_colors[i][j] = 0xFFFFFF;
src/init_grid.c:	grid->width = 80;
src/init_grid.c:	grid->height = 25;
src/init_grid.c:	grid->chunk = malloc(chunk_needed(grid));
src/init_grid.c:	if (!grid->chunk)
src/init_grid.c:	grid->x = 0;
src/init_grid.c:	grid->y = 0;
src/init_grid.c:	grid->spaces_per_tab = 4;
src/new_render_op.c:	grid->current_op->type = type;
src/new_render_op.c:	grid->current_op->x = x;
src/new_render_op.c:	grid->current_op->y = y;
src/new_render_op.c:	grid->current_op++; 
src/render.c:	s = &grid->screen[op->y][op->x];
src/render.c:		x11->tile_width * grid->width, x11->tile_height,
src/render.c:	while (y < grid->height) {
src/render.c:			grid->screen[y], grid->width
src/render.c:	grid->full_redraw = false;
src/render.c:		x11->tile_width * (grid->width - op->x), x11->tile_height,
src/render.c:	if (grid->full_redraw == true) {
src/render.c:	while (grid->operations[i].type != END_LIST && i < 4096) {
src/render.c:		grid->render_operation_functions[grid->operations[i].type]
src/render.c:			(x11, grid, &grid->operations[i]);
src/parse_escape_code.c:	grid->command_functions[(int)(**buffer - 'A')](grid, args, ac);
src/cursor_bounds_check.c:	return (grid->x == 0);
src/cursor_bounds_check.c:	return (grid->x == grid->width - 1);
src/cursor_bounds_check.c:	return (grid->y == grid->height - 1);
src/VT100_ABCD_commands.c:	grid->y--;
src/VT100_ABCD_commands.c:	grid->x++;
src/VT100_commands.c:	grid->x = args[1] - 1;
src/VT100_commands.c:	grid->y = args[0] - 1;
src/VT100_commands.c:	memmove(&grid->screen[grid->y][grid->x],
src/VT100_commands.c:		&grid->screen[grid->y][grid->x + args[0]],
src/VT100_commands.c:		(grid->width - (grid->x + 1) - args[0]) + (grid->width * (grid->height - grid->y + 1))
src/VT100_commands.c:	new_render_op(grid, DELETE_CHARACTER, grid->x, grid->y);
src/term_runtime.c:	ws.ws_row = grid->height;
src/term_runtime.c:	ws.ws_col = grid->width;
src/print_grid.c:		write(1, grid->screen[i], 80);
src/fill_grid.c:	while (y < grid->height - 1) {
src/fill_grid.c:		memmove(grid->screen[y], grid->screen[y + 1], grid->width * sizeof(char));
src/fill_grid.c:	memset(grid->screen[grid->height - 1], ' ', grid->width);
src/fill_grid.c:	grid->full_redraw = true;
src/fill_grid.c:	grid->x = 0;
src/fill_grid.c:		grid->x = 0;
src/fill_grid.c:		grid->y++;
src/fill_grid.c:	new_render_op(grid, PRINTABLE, grid->x, grid->y);
src/fill_grid.c:	grid->screen[grid->y][grid->x] = **buffer;
src/fill_grid.c:	grid->x++;
src/fill_grid.c:		grid->y--;
src/fill_grid.c:		grid->x = grid->width - 1;
src/fill_grid.c:		grid->x--;
src/fill_grid.c:		grid->y++;
src/fill_grid.c:	grid->x = 0;
src/fill_grid.c:		grid->x = 0;
src/fill_grid.c:		grid->y++;
src/fill_grid.c:		grid->x = 0;
src/fill_grid.c:	if (grid->width - (grid->x + 1) < grid->spaces_per_tab) {
src/fill_grid.c:	new_render_op(grid, PRINTABLE, grid->x, grid->y);
src/fill_grid.c:	grid->screen[grid->y][grid->x] = ' ';
src/fill_grid.c:	grid->x++;
src/fill_grid.c:	while (grid->x % grid->spaces_per_tab != 0) {
src/fill_grid.c:		new_render_op(grid, PRINTABLE, grid->x, grid->y);
src/fill_grid.c:		grid->screen[grid->y][grid->x] = ' ';
src/fill_grid.c:		grid->x++;
src/fill_grid.c:	bzero(grid->operations, sizeof(grid->operations));
src/fill_grid.c:	grid->current_op = grid->operations;
src/fill_grid.c:		grid->grid_functions[(unsigned char)*current](grid, &current);
src/fill_grid.c:	grid->current_op->type = END_LIST;
