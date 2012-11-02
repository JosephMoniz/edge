#ifndef EDGE_PATH_H_
#define EDGE_PATH_H_ 1

#include <string>
#include <initializer_list>

namespace edge {
class Path {
public:

  /**
   * This funciton takes a file system path as a std::string and
   * normalizes it. All redundant directory seperators are removed
   * all single dot directories are removed and all double dot
   * directories correctly traverse to the parent directory.
   *
   * EXAMPLES:
   *    edge::Path::normalize("/a/b/c/../d");    // -> /a/b/d
   *    edge::Path::normalize("/a/b/c/../../d"); // -> /a/d
   *    edge::Path::normalize("/b/wat//");       // -> /b/wat/
   *    edge::Path::normalize(/b///wat/);        // -> /b/wat/
   *    edge::Path::normalize("");               // -> .
   *    edge::Path::normalize("/");              // -> /
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
   *    edge::Path::join({"wat", "lol"});              // -> wat/lol
   *    edge::Path::join({"/a", "///b"});              // -> /a/b
   *    edge::Path::join({"/a", "b", "c", "..", "d"}); // -> /a/b/d
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
   *    edge::Path::dirname("wat.jpg");  // -> .
   *    edge::Path::dirname("/b/a.jpg"); // -> /b
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
   *    edge::Path::basename("wat.jpg");  // -> wat.jpg
   *    edge::Path::basename("/b/a.jpg"); // -> /b/a.jpg
   *    edge::Path::basename("/b/wat/");  // -> wat/
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
   *    edge::Path::basename("a.jpg", "jpg");    // -> a
   *    edge::Path::basename("/b/a.jpg", "jpg"); // -> a
   *    edge::Path::basename("/b/wat", "jpg");   // -> wat
   *    edge::Path::basename("/b/wat/", "jpg");  // -> wat/
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
   *    edge::Path::extname("lolwat.jpg"); // -> .jpg
   *    edge::Path::extname("/a/wat.jpg"); // -> .jpg
   *    edge::Path::extname("lolwat.");    // -> .
   *    edge::Path::extname("lolwat");     // ->
   *
   * @param {std::string} path - The path to extract the file extension from
   * @returns {std::string}    - The extracted file extension from the path
   */
  static std::string extname(std::string path);

private:
  static std::string::iterator _basenameIterator(std::string &path);

};
}

#endif
