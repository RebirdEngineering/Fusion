BEGIN_NAMESPACE(pf)
BEGIN_NAMESPACE(HttpRequest)
using namespace lang;

void Impl::Impl()
{
    //?
    throwError( HttpRequestException( Format("Creating HttpRequest failed")));
}

void Impl::Perform(String *)
{
    //?
    throwError(HttpRequestException());
}

void Impl::setHeader(String *)
{
    //?
    throwError(HttpRequestException( Format("Malformed header {0}", toString()));
}