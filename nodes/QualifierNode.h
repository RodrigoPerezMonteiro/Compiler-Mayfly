#ifndef __MF_QUALIFIERNODE_H__
#define __MF_QUALIFIERNODE_H__

#include <cdk/nodes/Node.h>

namespace mayfly {
namespace node {

class QualifierNode: public cdk::node::Node {
public:
inline QualifierNode(int lineno) :
cdk::node::Node(lineno) {
}

public:
const char *name() {
return "Qualifier";
}

void accept(SemanticProcessor *sp, int level) {
 sp->processQualifierNode(this, level);
}
};

} /* namespace node */
} /* namespace mayfly */
#endif
