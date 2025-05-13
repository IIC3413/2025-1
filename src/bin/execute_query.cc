#include <iostream>
#include <memory>

#include "query/parser/logical_plan/logical_plan.h"
#include "query/parser/parser.h"
#include "query/translator/optimizer.h"
#include "query/translator/passthrough.h"
#include "system/system.h"
#include "third_party/cli11/CLI11.hpp"

void select_query(std::unique_ptr<LogicalPlan> logical_plan, bool explain) {
  auto query_iter = Optimizer::create_physical_plan(std::move(logical_plan));

  if (explain) {
    std::cout << "Physical Plan:\n";
    std::cout << *query_iter << std::endl;
  }

  // print header
  auto out_cols = query_iter->get_columns();
  if (out_cols.size() > 0) {
    std::cout << out_cols[0].alias << '.' << out_cols[0].info.name;
  }
  for (size_t i = 1; i < out_cols.size(); i++) {
    std::cout << ',' << out_cols[i].alias << '.' << out_cols[i].info.name;
  }
  std::cout << '\n';

  uint64_t total_results = 0;
  auto& out = query_iter->get_output();
  query_iter->begin();
  while (query_iter->next()) {
    std::cout << out << '\n';
    total_results++;
  }
  std::cout << "\n got " << total_results << " results." << std::endl;
}

void edit_query(std::unique_ptr<LogicalPlan> logical_plan, bool explain) {
  auto action = PassThrough::create_physical_plan(std::move(logical_plan));
  if (explain) {
    std::cout << "Physical Plan:\n";
    std::cout << *action << std::endl;
  }
  action->execute();
}

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  uint64_t buffer_size = BufferManager::DEFAULT_BUFFER_SIZE;
  std::string db_directory;
  std::string query_file;
  bool explain = false;

  CLI::App app{"IIC 3413 DB"};
  app.get_formatter()->column_width(35);
  app.option_defaults()->always_capture_default();

  app.add_option("database", db_directory)
      ->description("Database directory")
      ->type_name("<path>")
      ->check(CLI::ExistingDirectory.description(""))
      ->required();

  app.add_option("query", query_file)
      ->description("The path to a text file with the query")
      ->type_name("<path>")
      ->check(CLI::ExistingFile.description(""));

  app.add_option("--buffer", buffer_size)
      ->description("Size of buffer\nAllows units such as MB and GB")
      ->option_text("<bytes> [1GB]")
      ->transform(CLI::AsSizeValue(false))
      ->check(CLI::Range(1024ULL * 1024, 1024ULL * 1024 * 1024 * 1024));

  app.add_flag("--explain", explain, "print logical and physical plan")->ignore_case();

  CLI11_PARSE(app, argc, argv);

  // Need to call System::init before start using the database
  // When this object comes out of scope the database is no longer usable
  auto system = System::init(db_directory, buffer_size);

  std::stringstream ss;
  if (query_file.empty()) {
    std::cout << "Query File not received as parameter.\n";
    std::cout << "Write the query in console and then press CTRL+D (EOF) to execute it" << std::endl;
    ss << std::cin.rdbuf();
    std::cout << '\n';
  } else {
    std::ifstream query_file_stream(query_file);
    ss << query_file_stream.rdbuf();
  }
  std::string query = ss.str();

  try {
    auto logical_plan = Parser::parse(query, explain);
    if (logical_plan->is_action()) {
      edit_query(std::move(logical_plan), explain);
    } else {
      select_query(std::move(logical_plan), explain);
    }
  } catch (const std::exception& e) {
    std::cout << "Query exception:\n";
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
