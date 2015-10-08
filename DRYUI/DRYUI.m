//
//  DRYUI.m
//
//  Created by Griffin Schneider on 3/3/15.
//  Copyright (c) 2015 Griffin Schneider. All rights reserved.
//

#import "DRYUI.h"
#import <objc/runtime.h>

_DRYUI_VIEW *_dryui_current_view = nil;
_DRYUI_VIEW *_dryui_current_toplevel_view = nil;


////////////////////////////////////////////////////////////////////////////////////////////////////
@interface _DRYUI_VIEW (DRYUI_Private)

@end

@implementation _DRYUI_VIEW (DRYUI_Private)


- (void)runAddBlock:(DRYUIViewAndSuperviewBlock)block {
    self.constraintMaker = [[MASConstraintMaker alloc] initWithView:self];
    self.wrappedAddBlocks = [NSMutableArray array];
    
    block(self, self.superview);
    
    [self.constraintMaker install];
    self.constraintMaker = nil;
    [self runAllWrappedAddBlocks];
}

@end


////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation DRYUIStyle
@end


////////////////////////////////////////////////////////////////////////////////////////////////////
id _dryui_instantiate_from_encoding(char *encoding) {
    NSString *encodingString = [NSString stringWithUTF8String:encoding];
    
    NSRange braceRange = [encodingString rangeOfString:@"{"];
    NSRange equalsRange = [encodingString rangeOfString:@"="];
    NSString *className = [encodingString substringWithRange:NSMakeRange(braceRange.location+braceRange.length, equalsRange.location-1)];
    
    id instance = [NSClassFromString(className) new];
    
    return instance;
}

void _dryui_addViewFromBuildSubviews(_DRYUI_VIEW *view, _DRYUI_VIEW *superview, DRYUIViewAndSuperviewBlock block) {
    [superview addSubview:view];
    
    // Don't actually need to weakify this reference since the block will get released
    // after it's run, but we get a block-retain-cycle warning without weakification.
    __weak _DRYUI_VIEW *weakView = view;
    
    // Add a block to view's superview's block list that does some setup, calls the given block, and then runs
    // all the blocks in view's block list (in order to run any blocks put there by calls to this method
    // from the given block).
    // view's superview's block list will eventually get run by the call to this method (or buildSubviews) that
    // recursed into this one.
    if (block) {
        [superview.wrappedAddBlocks addObject:^{
            [weakView runAddBlock:block];
        }];
    }
}


static const char dryui_constraintMakerId = 0;
static const char dryui_wrappedAddBlocksId = 0;
static const char dryui_stylesId = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation _DRYUI_VIEW (DRYUI)

- (void)_dryui_buildSubviews:(DRYUIViewAndSuperviewBlock)block {
    [self runAddBlock:block];
}

#define _DRYUI_VIEW_STRING _DRYUI_VIEW_STRING_HELPER(_DRYUI_VIEW)
#define _DRYUI_VIEW_STRING_HELPER(x) __DRYUI_VIEW_STRING_HELPER(x)
#define __DRYUI_VIEW_STRING_HELPER(x) @#x
- (MASConstraintMaker *)make {
    NSAssert(self.constraintMaker != nil, @"%@.make should only be used inside a call to buildSubviews.", _DRYUI_VIEW_STRING);
    [self setTranslatesAutoresizingMaskIntoConstraints:NO];
    return self.constraintMaker;
}

- (void)runAllWrappedAddBlocks {
    for (void(^block)() in self.wrappedAddBlocks) {
        block();
    }
    self.wrappedAddBlocks = nil;
}

- (NSMutableArray *)styles {
    NSMutableArray *retVal = objc_getAssociatedObject(self, &dryui_stylesId);
    if (!retVal) {
        retVal = [NSMutableArray array];
        objc_setAssociatedObject(self, &dryui_stylesId, retVal, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return retVal;
}

- (MASConstraintMaker *)constraintMaker {
    return objc_getAssociatedObject(self, &dryui_constraintMakerId);
}
- (void)setConstraintMaker:(MASConstraintMaker *)constraintMaker {
    objc_setAssociatedObject(self, &dryui_constraintMakerId, constraintMaker, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSMutableArray *)wrappedAddBlocks {
    return objc_getAssociatedObject(self, &dryui_wrappedAddBlocksId);
}
- (void)setWrappedAddBlocks:(NSMutableArray *)wrappedAddBlocks {
    objc_setAssociatedObject(self, &dryui_wrappedAddBlocksId, wrappedAddBlocks, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}




@end


////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation NSObject (DRYUI)

+ (instancetype)_dryui_selfOrInstanceOfSelf {
    return [self new];
}
- (instancetype)_dryui_selfOrInstanceOfSelf {
    return self;
}

@end

