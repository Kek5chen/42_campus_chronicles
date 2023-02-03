
export function RemoveLastDirectoryPartOf(url: string)
{
    var ret = url.split('/');
    ret.pop();
    return( ret.join('/') );
}
