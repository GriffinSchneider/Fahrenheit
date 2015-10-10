//
//  DRYUI.h
//
//  Created by Griffin Schneider on 3/3/15.
//  Copyright (c) 2015 Griffin Schneider. All rights reserved.
//


#if TARGET_OS_IPHONE
  #import <UIKit/UIKit.h>
  #define _DRYUI_VIEW UIView
#elif TARGET_OS_MAC
  #import <AppKit/AppKit.h>
  #define _DRYUI_VIEW NSView
#endif

#import <Foundation/Foundation.h>
#import <Masonry/Masonry.h>
#import <libextobjc/metamacros.h>
#import <objc/runtime.h>
#import "DRYUIMetamacros.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark Typedefs
@class DRYUIStyle;

typedef void (^DRYUIViewAndSuperviewBlock)(id _, _DRYUI_VIEW *superview);

////////////////////////////////////////////////////////////////////////////////////////////////////
@interface _DRYUI_VIEW (DRYUI)


@property (nonatomic, strong, readonly) MASConstraintMaker *make;
@property (nonatomic, strong, readonly) NSArray *styles;

- (void)_dryui_buildSubviews:(DRYUIViewAndSuperviewBlock)block;

@property (nonatomic, strong) MASConstraintMaker *constraintMaker;
@property (nonatomic, strong) NSMutableArray *wrappedAddBlocks;
- (void)runAllWrappedAddBlocks;

@end


////////////////////////////////////////////////////////////////////////////////////////////////////
@interface DRYUIStyle : NSObject
@end


////////////////////////////////////////////////////////////////////////////////////////////////////
@interface NSObject (DRYUI)
+ (instancetype)_dryui_selfOrInstanceOfSelf;
- (instancetype)_dryui_selfOrInstanceOfSelf;
@end


////////////////////////////////////////////////////////////////////////////////////////////////////
FOUNDATION_EXTERN _DRYUI_VIEW *_dryui_current_view;
FOUNDATION_EXTERN _DRYUI_VIEW *_dryui_current_toplevel_view;

FOUNDATION_EXTERN id _dryui_instantiate_from_encoding(char *);
FOUNDATION_EXTERN void _dryui_addViewFromBuildSubviews(_DRYUI_VIEW *view, _DRYUI_VIEW *superview, DRYUIViewAndSuperviewBlock block);


////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark Hierarchy Building Macros

#define build_subviews(args...) _build_subviews(args)

// Define some macros that will generate 'unique' variable names using __LINE__.
// The names will be unique as long as the DRYUI macros aren't used twice on the same line.
#define _dryui_var_passed_instance_or_nil metamacro_concat(_dryui_passedInstanceOrNil, __LINE__)
#define _dryui_var_view_and_superview_block metamacro_concat(_dryui_viewAndSuperviewBlockk, __LINE__)
#define _dryui_var_previous_toplevel_view metamacro_concat(_dryui_previousTopLevelView, __LINE__)
#define _dryui_var_saved_style_or_view metamacro_concat(_dryui_savedStyleOrView, __LINE__)
#define _dryui_goto_label metamacro_concat(_dryui_gotoLabel, __LINE__)

// body_after_statement_after_macro will get run *after* the statement formed by the end of this macro and whatever
// the user puts after the macro within {}.
// When body_after_statement_after_macro runs, this macro will have definied a variable with a name created by
// _dryui_var_view_and_superview_block, to which will be assigned a block of type DRYUIViewAndSuperviewBlock
// containing the code that came after the macro.
#define _dryui_goto_helper(viewArg, body_after_statement_after_macro) \
    DRYUIViewAndSuperviewBlock _dryui_var_view_and_superview_block; \
    if (1) { \
        NSAssert([NSThread isMainThread], @"DRYUI should only be used from the main thread!"); \
        goto _dryui_goto_label; \
    } else \
        while (1) \
            if (1) { \
                body_after_statement_after_macro \
                _dryui_var_view_and_superview_block = nil; \
                break; \
            } else \
                _dryui_goto_label: _dryui_var_view_and_superview_block = ^(typeof([viewArg _dryui_selfOrInstanceOfSelf]) _, _DRYUI_VIEW *superview) \
                // We couldn't get execution here without GOTOing here, but once we do and this statement finishes,
                // execution will jump back up to the while(1) and then into body_after_statement_after_macro.

#define _build_subviews(viewArg) \
    _DRYUI_VIEW *_dryui_var_previous_toplevel_view = _dryui_current_toplevel_view; \
    _dryui_current_toplevel_view = [viewArg _dryui_selfOrInstanceOfSelf]; \
    _dryui_goto_helper(viewArg, \
        [_dryui_current_toplevel_view _dryui_buildSubviews:_dryui_var_view_and_superview_block]; \
        _dryui_current_toplevel_view = _dryui_var_previous_toplevel_view; \
    )


#define add_subview(args...) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wunused-value\"") \
    _Pragma("clang diagnostic ignored \"-Wunused-getter-return-value\"") \
    metamacro_if_eq(1, metamacro_argcount(args)) ( \
        _dryui_add_subview1(args) \
    ) ( \
        metamacro_if_eq(2, metamacro_argcount(args)) ( \
            _dryui_add_subview2(args) \
        ) ( \
           _dryui_add_subviewMore(args) \
        ) \
    )\
    _Pragma("clang diagnostic pop") \


#define _dryui_add_subview1(variableName) _dryui_add_subview_helper_1(variableName, ;, ;)
#define _dryui_add_subview2(variableName, styleOrView) _dryui_add_subview_helper_2(variableName, styleOrView, ;)
#define _dryui_add_subviewMore_iter(idx, variableName, style) _dryui_addStyleToView(variableName, style(nil), self);
#define _dryui_add_subviewMore(variableName, styleOrView, ...) \
    _dryui_add_subview_helper_2(variableName, styleOrView, metamacro_foreach_cxt(_dryui_add_subviewMore_iter, , variableName, __VA_ARGS__ ))


// This macro passes through the first argument and codeAfterVariableAssignment to _dryui_add_subview_helper_2,
// while determining whether the second argument is a pre-made UIView instance or the first style to apply.
// The variable whose name comes from _dryui_var_passed_instance_or_nil will be set to the given UIView instance
// if the second argument is a UIView instance, or nil if it isn't. The variable whose name comes from
// _DRYUI_FIRST_STYLE_OR_NONE will be set to the given style if the second argument is a style, or the
// empty style if it isn't.
#define _dryui_add_subview_helper_2(variableName, styleOrView, codeAfterVariableAssignment) \
    _dryui_add_subview_helper_1(variableName, \
        /* Save styleOrView to a variable, since it might be an expression like '[UIView new' that we should only evaluate once */ \
        typeof(styleOrView) _dryui_var_saved_style_or_view = styleOrView; \
        _dryui_var_passed_instance_or_nil = _dryui_returnGivenViewOrNil(_dryui_var_saved_style_or_view); \
    , \
        _dryui_addStyleToView_acceptView(variableName, _dryui_var_saved_style_or_view, self); \
        codeAfterVariableAssignment \
    )

#define _dryui_add_subview_helper_1(variableName, codeAfterVariableDeclarations, codeAfterVariableAssignment) \
    variableName ; \
    typeof(variableName) _dryui_var_passed_instance_or_nil = nil; \
    codeAfterVariableDeclarations \
    if (!variableName) { \
        variableName = _dryui_var_passed_instance_or_nil ?: _dryui_instantiate_from_encoding(@encode(typeof(*(variableName)))); \
    } \
    NSAssert(_dryui_current_toplevel_view, @"Calls to DRYUI must be inside a call to DRYUI_TOPLEVEL."); \
    _dryui_current_view = variableName; \
    _dryui_goto_helper(variableName, \
        _dryui_addViewFromBuildSubviews(_dryui_current_view, _, _dryui_var_view_and_superview_block); \
        ({ codeAfterVariableAssignment }); \
        _dryui_current_view = nil; \
    ) \


static inline id __attribute((overloadable, unused)) _dryui_returnGivenViewOrNil(_DRYUI_VIEW *view) {
    return view;
}

static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView_acceptView(_DRYUI_VIEW *view, _DRYUI_VIEW *notAStyle, id selfForBlock) {
    
}

static inline id __attribute((overloadable, unused)) _dryui_returnGivenStyleOrNil(_DRYUI_VIEW *notAStyle) {
    return nil;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Style Macros

/*!
 * This it the dox
 * dox dox dox
 */
#define dryui_style(args...) _dryui_style(args)

#define dryui_public_style(args...) _dryui_public_style(args)
#define dryui_private_style(args...) _dryui_private_style(args)

#define dryui_applyStyle(view, style, selfForStyle) _dryui_addStyleToView(view, style(nil), selfForStyle)
#define dryui_parentStyle(style) _dryui_addStyleToView_internal(_, style(nil), self)



////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Style Macro Implementation

// Private styles are just the public style declaration and then the style implementation
#define _dryui_private_style(args...) \
    dryui_public_style(args) dryui_style(args)

// Helper macros that generate static variable names that store all the actual style data
#define _dryui_style_class_name(styleName) \
    metamacro_concat(_DRYUI_Style_, styleName)
#define _dryui_style_application_block_variable_name(styleName) \
    metamacro_concat(_DRYUI_StyleAplicationBlock_, styleName)

// 'nil', casted to an instance of the class for the given style.
// This is used to select the correct overloaded function for our style
#define _dryui_nil_casted_to_instance_of_style_class(styleName) \
    ((_dryui_style_class_name(styleName)*)nil)

// Passed an argument list like this:
//    (NSString *)firstArg, (NSString *)secondArg
// _dryui_extract_variable_nameS will expand to a list containing just the variable names:
//    firstArg, secondArg
#define _dryui_remove_arg_type(arg)
#define _dryui_extract_variable_name(idx, argWithType) \
    _dryui_remove_arg_type argWithType
#define _dryui_extract_variable_nameS(argsWithTypes...) \
    metamacro_if_eq(1, metamacro_argcount(bogus , ##argsWithTypes )) ( \
        /* nothing */ \
    ) ( \
        metamacro_foreach_sep_macro(_dryui_extract_variable_name, metamacro_comma_sep , ##argsWithTypes ) \
    ) \

// Passed an argument list like this:
//    (NSString *)firstArg, (NSString *)secondArg
// _dryui_extract_arguments will expand to a normally-formatted list of function arguments with types
//    NSString *firstArg, NSString *secondArg
#define _dryui_remove_parens_from_arg_type(argWithType) \
    argWithType
#define _dryui_remove_parens_from_arg_type_iter(idx, argWithType) \
    _dryui_remove_parens_from_arg_type argWithType
#define _dryui_extract_arguments(argsWithTypes...) \
    metamacro_if_eq(1, metamacro_argcount(bogus , ##argsWithTypes )) ( \
        /* nothing */ \
    ) ( \
        metamacro_foreach_sep_macro(_dryui_remove_parens_from_arg_type_iter, metamacro_comma_sep , ##argsWithTypes ) \
    )

#define _dryui_public_style(args...) \
    metamacro_if_eq(1, metamacro_argcount(args)) ( \
        dryui_public_style1(args) \
    ) ( \
        metamacro_if_eq(2, metamacro_argcount(args)) ( \
            dryui_public_style2(args) \
        ) ( \
            dryui_public_styleMore(args) \
        ) \
    ) \

#define dryui_public_style1(styleName) dryui_public_style2(styleName, _DRYUI_VIEW)
#define dryui_public_style2(styleName, className) dryui_public_styleMore(styleName, className)
#define dryui_public_styleMore(styleName, className, ...) \
    @interface _dryui_style_class_name(styleName) : DRYUIStyle \
    @end  \
    \
    typedef void (^_DRYUI_applicationBlockForStyle_##styleName)(id _, _DRYUI_VIEW *superview, id self metamacro_comma_if_any_args( __VA_ARGS__ ) _dryui_extract_arguments( __VA_ARGS__ )); \
    FOUNDATION_EXTERN _DRYUI_applicationBlockForStyle_##styleName _dryui_style_application_block_variable_name(styleName); \
    \
    metamacro_if_eq(1, metamacro_argcount(bogus , ##__VA_ARGS__ )) ( \
        _dryui_typedefs_no_args(styleName, className) \
    ) ( \
        _dryui_typedefs_some_args(styleName, className , ##__VA_ARGS__ ) \
    )

#define _dryui_typedefs_no_args(styleName, className) \
    typedef void (^_DRYUI_blockThatGetsPassedByAddStyleToView_##styleName )(); \
    typedef void                                            (^_DRYUI_blockReturnedByBlockForStyle_##styleName)( _dryui_style_class_name(styleName)*, _DRYUI_blockThatGetsPassedByAddStyleToView_##styleName blockFromAddStyleToView); \
    typedef _DRYUI_blockReturnedByBlockForStyle_##styleName (^_DRYUI_blockForStyle_##styleName)(_dryui_style_class_name(styleName)*); \
    \
    FOUNDATION_EXTERN _DRYUI_blockForStyle_##styleName styleName; \
    \
    static inline id __attribute((overloadable, unused)) _dryui_returnGivenViewOrNil(_DRYUI_blockForStyle_##styleName notAView) { \
        return nil; \
    } \
    static inline id __attribute((overloadable, unused)) _dryui_returnGivenStyleOrNil(_DRYUI_blockForStyle_##styleName style) { \
        return style; \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView_internal(className *view, _DRYUI_blockReturnedByBlockForStyle_##styleName firstLevelBlock, id selfForBlock) { \
        firstLevelBlock(_dryui_nil_casted_to_instance_of_style_class(styleName), ^() { \
            _dryui_style_application_block_variable_name(styleName)(view, view.superview, selfForBlock); \
        }); \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView(className *view, _DRYUI_blockReturnedByBlockForStyle_##styleName firstLevelBlock, id selfForBlock) { \
        id oldConstraintMaker = view.constraintMaker; \
        view.constraintMaker = [[MASConstraintMaker alloc] initWithView:view]; \
        view.wrappedAddBlocks = [NSMutableArray array]; \
        \
        _dryui_addStyleToView_internal(view, firstLevelBlock, selfForBlock); \
        \
        [view.constraintMaker install]; \
        view.constraintMaker = oldConstraintMaker; \
        [view runAllWrappedAddBlocks]; \
        [((NSMutableArray *)view.styles) addObject:styleName]; \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView_acceptView(className *view, _DRYUI_blockForStyle_##styleName firstLevelBlock, id selfForBlock) { \
        _dryui_addStyleToView(view, firstLevelBlock(nil), selfForBlock);\
    } \


#define _dryui_typedefs_some_args(styleName, className, ...) \
    typedef void (^_DRYUI_blockThatGetsPassedByAddStyleToView_##styleName )(_dryui_extract_arguments( __VA_ARGS__)); \
    typedef void                                                           (^_DRYUI_blockReturnedByBlockReturnedByBlockForStyle_##styleName)( _dryui_style_class_name(styleName)*, _DRYUI_blockThatGetsPassedByAddStyleToView_##styleName blockFromAddStyleToView); \
    typedef _DRYUI_blockReturnedByBlockReturnedByBlockForStyle_##styleName (^_DRYUI_blockReturnedByBlockForStyle_##styleName)(_dryui_style_class_name(styleName)*); \
    typedef _DRYUI_blockReturnedByBlockForStyle_##styleName                (^_DRYUI_blockForStyle_##styleName)(_dryui_extract_arguments( __VA_ARGS__)); \
    \
    FOUNDATION_EXTERN _DRYUI_blockForStyle_##styleName styleName; \
    \
    static inline id __attribute((overloadable, unused)) _dryui_returnGivenViewOrNil(_DRYUI_blockReturnedByBlockForStyle_##styleName notAView) { \
        return nil; \
    } \
    static inline id  __attribute((overloadable, unused)) _dryui_returnGivenStyleOrNil(_DRYUI_blockReturnedByBlockForStyle_##styleName style) { \
        return style(nil); \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView_internal(className *view, _DRYUI_blockReturnedByBlockReturnedByBlockForStyle_##styleName secondLevelBlock, id selfForBlock) { \
        secondLevelBlock(_dryui_nil_casted_to_instance_of_style_class(styleName), ^(_dryui_extract_arguments( __VA_ARGS__ )) { \
            _dryui_style_application_block_variable_name(styleName)(view, view.superview, selfForBlock metamacro_comma_if_any_args( __VA_ARGS__ ) _dryui_extract_variable_nameS( __VA_ARGS__ )); \
        }); \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView(className *view, _DRYUI_blockReturnedByBlockReturnedByBlockForStyle_##styleName secondLevelBlock, id selfForBlock) { \
        id oldConstraintMaker = view.constraintMaker; \
        view.constraintMaker = [[MASConstraintMaker alloc] initWithView:view]; \
        view.wrappedAddBlocks = [NSMutableArray array]; \
        \
        _dryui_addStyleToView_internal(view, secondLevelBlock, selfForBlock); \
        \
        [view.constraintMaker install]; \
        view.constraintMaker = oldConstraintMaker; \
        [view runAllWrappedAddBlocks]; \
        [((NSMutableArray *)view.styles) addObject:styleName]; \
        \
    } \
    static inline void __attribute__((overloadable, unused)) _dryui_addStyleToView_acceptView(className *view, _DRYUI_blockReturnedByBlockForStyle_##styleName secondLevelBlock, id selfForBlock) { \
        _dryui_addStyleToView(view, secondLevelBlock(nil), selfForBlock); \
    } \



// Style implementation
//
// In order to get the nice syntax where you just put curly braces after the macro, this has to expand to a
// bunch of stuff and then the beginning of a block literal. So, declare a static variable for the block,
// override the applicationBlock getter to return that static variable, and then actually assign the
// block to the var at the very end.
//
// When you refer to the style, (i.e. 'DRYUIEmptyStyle'), you're actually referencing a static variable
// that contains a singleton instance of the class implemented here. We can't assign to that variable statically,
// so instead we assign it when our class gets the 'load' message.
//
// Styles make heavy use of __attribute__((overloadable)) to get type safety for style application. Every style
// declares additional overloaded versions of the _dryui_addStyleToView and _dryui_addStyleToView_acceptView
// functions that take the UIView subclass that the style applies to as the first argument, and an instance of the
// style's class as the second argument. This means that, for example, if you declare a style named 'ButtonStyle'
// that applies only to 'UIButton*', then there is no version of _dryui_addStyleToView that takes a 'UIView*' and
// a 'ButtonStyle', which will cause a compiler warning if you try to apply 'ButtonStyle' to a UIView!
//
// The _dryui_addStyleToView_acceptView function is a hack to support the case where the second argument to add_subview
// is a UIView instance - this function has 1 additional overloaded version where the first and second arguments are
// UIViews, so that you won't get a compiler warning about there being a UIView where we expect a DRYUIStyle.


#define _dryui_style(args...) \
    metamacro_if_eq(1, metamacro_argcount(args)) ( \
        _dryui_style1(args) \
    ) ( \
        metamacro_if_eq(2, metamacro_argcount(args)) ( \
            _dryui_style2(args) \
        ) ( \
            _dryui_styleMore(args) \
        ) \
    )

#define _dryui_style1(styleName) _dryui_style2(styleName, _DRYUI_VIEW)
#define _dryui_style2(styleName, className) _dryui_styleMore(styleName, className)
#define _dryui_styleMore(styleName, className, ...) \
    @implementation _dryui_style_class_name(styleName) \
    @end \
    dryui_block_for_style(styleName, className , ##__VA_ARGS__ ); \
    _DRYUI_applicationBlockForStyle_##styleName _dryui_style_application_block_variable_name(styleName) = ^(className *_, _DRYUI_VIEW *superview, id self metamacro_comma_if_any_args( __VA_ARGS__ ) _dryui_extract_arguments( __VA_ARGS__ )) \


#define dryui_block_for_style(styleName, className, ...) \
    metamacro_if_eq(1, metamacro_argcount(bogus , ##__VA_ARGS__ )) ( \
        dryui_block_for_style_no_args(styleName, className) \
    ) ( \
        dryui_block_for_style_some_args(styleName, className , ##__VA_ARGS__ ) \
    )

#define dryui_block_for_style_no_args(styleName, className) \
    _DRYUI_blockForStyle_##styleName styleName = ^_DRYUI_blockReturnedByBlockForStyle_##styleName(_dryui_style_class_name(styleName)* bogus) { \
        return ^(_dryui_style_class_name(styleName) *style, _DRYUI_blockThatGetsPassedByAddStyleToView_##styleName blockFromAddStyleToView) { \
            return blockFromAddStyleToView(); \
        }; \
    }; \

#define dryui_block_for_style_some_args(styleName, className, ...) \
    _DRYUI_blockForStyle_##styleName styleName = ^_DRYUI_blockReturnedByBlockForStyle_##styleName( _dryui_extract_arguments( __VA_ARGS__ ) ) { \
        return ^_DRYUI_blockReturnedByBlockReturnedByBlockForStyle_##styleName(_dryui_style_class_name(styleName)* bogus) { \
            return ^(_dryui_style_class_name(styleName) *style, _DRYUI_blockThatGetsPassedByAddStyleToView_##styleName blockFromAddStyleToView) { \
                return blockFromAddStyleToView(_dryui_extract_variable_nameS( __VA_ARGS__ )); \
            }; \
        }; \
    }; \
