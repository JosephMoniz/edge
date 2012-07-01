#include <string>
#include <initializer_list>

namespace node {
class Path {
public:

  /**
   * This funciton takes a file system path as a std::string and
   * normalizes it. All redundant directory seperators are removed
   * all single dot directories are removed and all double dot
   * directories correctly traverse to the parent directory.
   *
   * EXAMPLES:
   *    node::Path::normalize("/a/b/c/../d");    // -> /a/b/d
   *    node::Path::normalize("/a/b/c/../../d"); // -> /a/d
   *    node::Path::normalize("/b/wat//");       // -> /b/wat/
   *    node::Path::normalize(/b///wat/);        // -> /b/wat/
   *    node::Path::normalize("");               // -> .
   *    node::Path::normalize("/");              // -> /
   *
   * @param {std::string} path - The path to normalize
   * @returns {std::string}    - The normalized path
   */
  static std::string normalize(std::string path);

  /**
   * This is a variadic function that takes any number of fragments for
   * a filesystem path, concatenates them together and performs path
   * normalization on the result.
   *
   * EXAMPLES:
   *    node::Path::join({"wat", "lol"});              // -> wat/lol
   *    node::Path::join({"/a", "///b"});              // -> /a/b
   *    node::Path::join({"/a", "b", "c", "..", "d"}); // -> /a/b/d
   *
   * @param {std::string ...} peices - The peices of the filesystem path to
   *                                   join together and normalize
   * @returns {std::string}          - The normalized path
   */
  static std::string join(std::initializer_list<std::string> peices);

  /**
   * This functin takes a file system path as a std::string and
   * returns the directory path.
   *
   * EXAMPLES:
   *    node::Path::dirname("wat.jpg");  // -> .
   *    node::Path::dirname("/b/a.jpg"); // -> /b
   *
   * @param {std::string} path - The path to extract the director path from
   * @returns {std::string}    - The extracted directory path
   */
  static std::string dirname(std::string path);

  /**
   * This funciton takes a file system path as a std::string and returns
   * the basename portion of that path.
   *
   * EXAMPLES:
   *    node::Path::basename("wat.jpg");  // -> wat.jpg
   *    node::Path::basename("/b/a.jpg"); // -> /b/a.jpg
   *    node::Path::basename("/b/wat/");  // -> wat/
   *
   * @param {std::string} path - The path to extract the basename from
   * @returns {std::string}    - The extracted basename from the path
   */
  static std::string basename(std::string path);

  /**
   * This function takes a file system path as a std::string and a
   * file extension as a string and returns the basename from the path
   * with the file extension removed. The file extension of the basename
   * will only be removed if it matches the file extension passed in.
   *
   * EXAMPLES:
   *    node::Path::basename("a.jpg", "jpg");    // -> a
   *    node::Path::basename("/b/a.jpg", "jpg"); // -> a
   *    node::Path::basename("/b/wat", "jpg");   // -> wat
   *    node::Path::basename("/b/wat/", "jpg");  // -> wat/
   *
   * @param {std::string} path - The path to extract the basename from
   * @param {std::string} ext  - The extension to exclude from the basename
   * @returns {std::string}    - The extracted basename from the path
   */
  static std::string basename(std::string path, std::string ext);

  /**
   * This funciton takes a file system path as a std::string and returns
   * the file extension as a std::string
   *
   * EXAMPLES:
   *    node::Path::extname("lolwat.jpg"); // -> .jpg
   *    node::Path::extname("/a/wat.jpg"); // -> .jpg
   *    node::Path::extname("lolwat.");    // -> .
   *    node::Path::extname("lolwat");     // ->
   *
   * @param {std::string} path - The path to extract the file extension from
   * @returns {std::string}    - The extracted file extension from the path
   */
  static std::string extname(std::string path);

private:
  static std::string::iterator _basenameIterator(std::string &path);

};
}
