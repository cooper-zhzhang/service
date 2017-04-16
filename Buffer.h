#ifndef BUFFER_H
#define BUFFER_H

#include <vector>



class Buffer
{
  public:
    static const size_t INITSIZE = 1024;
    static const size_t PREPEND = sizeof(unsigned long);//在64位电脑中占8位
    explicit Buffer(size_t initSize = Buffer::INITSIZE):
      buffer_(Buffer::INITSIZE), readerIndex_(Buffer::PREPEND), writeIndex_(Buffer::PREPEND)
  {
  }

    ~Buffer()
    {
    }

    unsigned long peekUlong()
    {
      std::string result(peek(), sizeof(unsigned long));
      retrieve(sizeof(unsigned long));
      return std::stoul(result);
    }

    size_t prepenableBytes()
    {
      return readerIndex_;
    }

    size_t readableBytes() const
    {
      return writeIndex_ - readerIndex_;
    }

    size_t writableBytes() const
    {
      return buffer_.size() - writeIndex_;
    }

    const char* peek()
    {
      return begin() + readerIndex_;
    }

    void retrieveAll()
    {
      readerIndex_ = PREPEND;
      writeIndex_ = PREPEND;
    }

    std::string retrieveAllAsString()
    {
      return retrieveAsString(readableBytes());
    }

    std::string retrieveAsString(size_t len)
    {
      std::string result(peek(), len);
      retrieve(len);
      return result;
    }

    void retrieve(size_t len)
    {
      if(len < readableBytes())
      {
        readerIndex_ += len;
      }
      else
      {
        retrieveAll();
      }
    }

    void append(const std::string data)
    {
      append(string.data(), data.size());
    }

    void append(const void *data, size_t len)
    {
      append(static_cast<const char*>(data), len);
    }

    void append(const char *data, size_t len)
    {
      ensureWritableBytes(len);
      std::copy(data, data + len, beginWrite());
      hasWritten(len);
    }

    void ensureWritableBytes(size_t len)
    {
      if(writableBytes() < len)
      {
        makespace(len);
      }
    }

    void hasWritten(size_t len)
    {
      writeIndex_ += len;
    }

  private:

    void makespace(size_t len)
    {
      if(readerIndex_ + writableBytes() < len + Buffer::PREPEND)
      {
        buffer_.resize(len + writeIndex_);
      }
      else
      {
        size_t readable = readableBytes();
        std::copy(begin() + readerIndex_, begin() + writeIndex_, begin() + PREPEND);
        readerIndex_ = PREPEND;
        writeIndex_ = readerIndex_ + readable;
      }

    }

    char* begin()
    {
      return &*buffer_.begin();
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writeIndex_;
};
#endif
