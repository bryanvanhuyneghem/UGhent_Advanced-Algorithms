#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::map;
using std::ostream;
using std::string;
using std::vector;

typedef unsigned char uchar;
const uchar epsilon = 0;

typedef unsigned char uchar;

class DA {
  friend ostream& operator<<(ostream&, const DA&);

 public:
  DA(std::string patroon);
  bool zitInTweet(const std::string& tekst, int& vergelijkingen);

 private:
  struct DAToestand {
    bool eindToestand;
    map<uchar, int> overgangen;
  };

  // 0: begintoestand
  vector<DAToestand> toestanden;
  string patroon;
};
