//ifstream infile("D:time.txt", ios::in | ios::binary | ios::ate);
		//if (infile.is_open()) {
		//	size_t in_file_size = static_cast<size_t>(infile.tellg());
		//	cout << "file: " << "D:time.txt" << " - is opened, size = " << in_file_size << " \n";
		//	vector<char> data_array(in_file_size);
		//	infile.seekg(0, ios::beg);
		//	atomic<size_t> read_pos(0);
		//	size_t const read_by_size = 1024 * 1024;	// 1 MB
		//	condition_variable cv_read;
		//	mutex mtx_read;
		//	thread t_read_file([&]() {
		//		while (read_pos < in_file_size) {
		//			size_t current_read_bytes = min(read_by_size, (size_t)in_file_size - read_pos);
		//			infile.read(data_array.data(), current_read_bytes);
		//			read_pos += current_read_bytes;
		//			cv_read.notify_all();
		//		}
		//		cout << "thread read ended \n";
		//	});
		//	size_t current_pos;
		//	for (current_pos = 0; current_pos < in_file_size;) {
		//		size_t tmp_read_pos = read_pos;
		//		if (tmp_read_pos > current_pos) {
		//			for (size_t i = current_pos; i < tmp_read_pos; ++i) {
		//				data_array[i] = data_array[i] * 2;	// process data
		//			}
		//		}
		//		else {
		//			for (unique_lock<mutex> lock(mtx_read); read_pos <= current_pos; cv_read.wait(lock));
		//		}
		//		current_pos = tmp_read_pos;
		//	}
		//	t_read_file.join();
		//	cout << "current_pos = " << current_pos << " \n";
		//	cout << "read_pos = " << read_pos << " \n";
		//}

		//cout << "OK \n";
		//getchar();