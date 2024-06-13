#include <fmt/core.h>
#include <pqxx/pqxx>
#include <random>
#include <vector>

std::minstd_rand g_rng;

class PQXXConnection {
public:
	PQXXConnection() : conn(getConnString()) {} // will throw if credentials are invalid

	std::string getConnString() {
		std::string conn_url = std::getenv("DB_URL");
		// TODO: check if null
		return conn_url;
	}

	pqxx::result query(const std::string &q) {
    	try {
			pqxx::work worker = pqxx::work(conn);
			pqxx::result row = worker.exec(q);
			worker.commit();
			return row;
    	} catch (const std::exception &e) {
			fmt::print(stderr, "ERROR: query {} failed:\n{}\n", q, e.what());
			return {};
    	}
    	return {};
	}

private:
	// none shall pass!!
	PQXXConnection(PQXXConnection &&) {}
	PQXXConnection(PQXXConnection &) {}
	PQXXConnection& operator=(PQXXConnection &) { return *this; }
	PQXXConnection& operator=(PQXXConnection &&) { return *this; }

	pqxx::connection conn;
};

struct TradingCard {
	double batting_average;
	double price;
	std::string name;
};

double randomDouble(std::minstd_rand &rng) {
	return std::generate_canonical<double, 16>(rng);
}

std::vector<TradingCard> generateTradingCards() {
	std::vector<TradingCard> cards = {};

	cards.push_back({randomDouble(g_rng), randomDouble(g_rng), "Bob Jones"});
	cards.push_back({randomDouble(g_rng), randomDouble(g_rng), "John Smith"});
	cards.push_back({randomDouble(g_rng), randomDouble(g_rng), "Kenny Bean"});

	return cards;
}

int main() {
	std::random_device r;
	std::seed_seq seed = {r(), r(), r(), r()};
	g_rng = std::minstd_rand(seed);

	fmt::print("random 16bit double {}\n", randomDouble(g_rng));
	std::vector<TradingCard> cards = generateTradingCards();

	try {
		PQXXConnection conn = {};

		// TODO: put this in a test case
		pqxx::result result = conn.query("SELECT 1");
		if (result.size()) {
			fmt::print("good result: {}\n", result.at(0).at(0).as<int>());
		} else {
			fmt::print("bad result\n");
		}

#if 0
		auto card = TradingCard{0.234, 4.20, "Fred Jones"};
		std::string q = fmt::format("INSERT INTO trading_cards (name,batting_average,price) VALUES ('{}',{},{})", card.name, card.batting_average, card.price);
		result = conn.query(q);
#endif

		result = conn.query("SELECT * FROM trading_cards WHERE id>0");
		if (result.size()) {
			fmt::print("found: {}\n", result.at(0).at(0).as<int>());
		} else {
			fmt::print("search all found no matches\n");
		}

	} catch (const std::exception &e) {
		fmt::print(stderr, "FATAL: Likely invalid connection string:\n{}\n", e.what());
	}
}
