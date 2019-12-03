#include <fstream>
#include <iostream>
#include <sstream>

constexpr auto CSV_OPEN_ERROR = 1;
constexpr auto HTML_OPEN_ERROR = 2;

int main() {
	std::string line;
	bool is_header = true;
	std::fstream csv, html;

	csv.open("csv_to_html_res.csv");
	if (!csv) goto HANDLE_CSV_OPEN_ERROR;

	html.open("index.html", std::ios::out);
	if (!html) goto HANDLE_HTML_OPEN_ERROR;

	html << "<html><body><table>" << std::endl;
	while (getline(csv, line)) {
		html << "<tr>";
		std::istringstream iss(line);
		std::string col;
		while (getline(iss, col, ','))
			html << (is_header ? "<th>" : "<td>")
				 << col
				 << (is_header ? "</th>" : "</td>");
		html << "</tr>" << std::endl;
		is_header = false;
	}
	html << "</table></body></html>" << std::endl;
	csv.close();
	html.close();
	return 0;

HANDLE_CSV_OPEN_ERROR:
	return CSV_OPEN_ERROR;
HANDLE_HTML_OPEN_ERROR:
	csv.close();
	return HTML_OPEN_ERROR;
}
