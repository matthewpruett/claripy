__all__ = [ 'LazyArg', 'Expr', 'Bits' ]

from claricpp import *
import annotation_spav
from functools import cache, cached_property

# TODO: deal with destruction / freeing memory
# TODO: slots!


class LazyArg:
    '''
    Wraps a Claricpp Arg ( my_expr.arg(i) is of this type ). The .arg value is lazily evaluated
    '''
    def __init__(self, raw):
        self._raw = raw

    @cached_property
    def arg(self):
        '''
        Returns the python arg generated from the Claricpp object raw
        '''
        return self._gen_arg()

    def _gen_arg(self):
        '''
        Generates and sets _arg given self._raw
        '''
        tp = self._raw.type
        # Primitive
        if tp == claricpp.ClaricppTypeEnumBool:
            self._arg = bool(self._raw.data.prim.boolean)
        elif tp == claricpp.ClaricppTypeEnumStr:
            self._arg = to_utf8(self._raw.data.prim.str)
        elif tp == claricpp.ClaricppTypeEnumFloat:
            self._arg = self._raw.data.prim.flt
        elif tp == claricpp.ClaricppTypeEnumDouble:
            self._arg = self._raw.data.prim.dbl
        elif tp == claricpp.ClaricppTypeEnumVS:
            raise NotImplementedError() # TODO: implement
        elif tp == claricpp.ClaricppTypeEnumU8:
            self._arg = self._raw.data.prim.u8
        elif tp == claricpp.ClaricppTypeEnumU16:
            self._arg = self._raw.data.prim.u16
        elif tp == claricpp.ClaricppTypeEnumU32:
            self._arg = self._raw.data.prim.u32
        elif tp == claricpp.ClaricppTypeEnumU64:
            self._arg = self._raw.data.prim.u64
        # Not primitive
        elif tp == claricpp.ClaricppTypeEnumBigInt:
            self._arg = to_utf8(self._raw.data.big_int)
        elif tp == claricpp.ClaricppTypeEnumExpr:
            self._arg = Expr(self._raw.data.expr)
        elif tp == claricpp.ClaricppTypeEnumRM:
            self._arg = RM(self._raw.data.rm)
        elif tp == claricpp.ClaricppTypeEnumWidth:
            self._arg = Width(self._raw.data.width)
        # Invalid
        else:
            raise NotImplementedError('Unknown Arg type: ' + str(self._raw.type))
        return self._arg

class Expr:
    '''
    The claripy API for a claricpp Expr Base
    '''
    def __init__(self, expr):
        self._expr = expr

    @cached_property
    def symbolic(self) -> bool:
        return bool(claricpp.claricpp_expr_symbolic(self._expr))

    @cached_property
    def lazy_args(self) -> list[LazyArg]:
        '''
        Return the raw LazyArg's contained by self
        '''
        c_arr = claricpp.claricpp_expr_args(self._expr)
        arr = c_arr.arr
        return [ LazyArg(arr[i]) for i in range(c_arr.len) ]

    @cached_property
    def args(self):
        '''
        Return the args contained by self
        '''
        return [ i.arg for i in self.lazy_args ]

    def __repr__(self) -> str:
        return to_utf8(claricpp.claricpp_expr_repr(self._expr))

    @cached_property
    def type_name(self) -> str:
        return to_utf8(claricpp.claricpp_expr_type_name(self._expr))

    @cached_property
    def op_name(self) -> str:
        return to_utf8(claricpp.claricpp_expr_op_name(self._expr))

    @cached_property
    def annotations() -> annotation_spav:
        return AnnotationSPAV(claricpp.claricpp_expr_annotations(self._expr))

    @cached_property
    def raw(self):
        '''
        Get the raw expr self holds
        Warning: Do not call this function unless you know what you are doing!
        '''
        return self._expr

class Bits(Expr):
    '''
    The claripy API for a claricpp Expr Bits
    '''
    def __init__(self, raw):
        super().__init__(raw)

    @cache
    def __len__(self) -> int:
        return claricpp.claricpp_expr_bit_length(self._expr)